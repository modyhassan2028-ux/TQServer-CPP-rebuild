# end-to-end market flow against live MariaDB, same SQL shapes as CAccountManager
import subprocess
def q(sql):
    r = subprocess.run(["mariadb", "-u", "tqserver", "-ptqpass123", "tqserver", "-N", "-e", sql],
                       capture_output=True, text=True)
    if r.returncode != 0:
        print("SQL FAILED:", r.stderr.strip()); raise SystemExit(1)
    return r.stdout.strip()

q("DELETE FROM cq_market"); q("DELETE FROM cq_mail WHERE to_name IN ('SellerX')")
q("DELETE FROM cq_user WHERE account_id=99002")
q("INSERT INTO cq_user (account_id, name, level, money, cp, bank) VALUES (99002, 'SellerX_char', 10, 0, 0, 0)")
q("INSERT INTO cq_market (seller_name, item_type, item_name, sort, amount, plus, enchant, price) "
  "VALUES ('SellerX', 410051, 'RefinedSword', 1, 1, 3, 0, 25000)")
mid = q("SELECT MAX(id) FROM cq_market")          # AUTO_INCREMENT is not reset by DELETE
assert mid.isdigit(), mid
row = q(f"SELECT seller_name, price, is_sold, amount, plus FROM cq_market WHERE id={mid}")
assert row == "SellerX\t25000\t0\t1\t3", row
# buyer1 claims atomically (affected rows = 1, same session as the UPDATE)
assert q(f"UPDATE cq_market SET is_sold=1 WHERE id={mid} AND is_sold=0; SELECT ROW_COUNT();") == "1"
# buyer2 races on the sold row: claim must affect 0 rows
assert q(f"UPDATE cq_market SET is_sold=1 WHERE id={mid} AND is_sold=0; SELECT ROW_COUNT();") == "0"
# proceeds -> seller's bank (offline credit by name) + notification mail
q("UPDATE cq_user SET bank = bank + 25000 WHERE name='SellerX_char'")
q("INSERT INTO cq_mail (to_name, from_name, body) VALUES ('SellerX','MARKET','BuyerY bought your RefinedSword for 25000')")
assert q("SELECT bank FROM cq_user WHERE name='SellerX_char'") == "25000"
assert q("SELECT to_name FROM cq_mail WHERE to_name='SellerX'") == "SellerX"
# claimed row keeps its data for the buyer fetch
assert q(f"SELECT item_name, plus, price FROM cq_market WHERE id={mid}") == "RefinedSword\t3\t25000"
q("DELETE FROM cq_market"); q("DELETE FROM cq_mail WHERE to_name='SellerX'")
q("DELETE FROM cq_user WHERE account_id=99002")
print("MARKET_SQL_OK: listing, atomic claim (1 then 0), bank credit, seller mail")
