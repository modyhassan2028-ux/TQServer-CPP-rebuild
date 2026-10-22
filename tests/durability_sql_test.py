import subprocess
def q(sql):
    r = subprocess.run(["mariadb", "-u", "tqserver", "-ptqpass123", "tqserver", "-N", "-e", sql],
                       capture_output=True, text=True)
    if r.returncode != 0:
        print("SQL FAILED:", r.stderr.strip()); raise SystemExit(1)
    return r.stdout.strip()
q("DELETE FROM cq_item WHERE account_id=99003")
# the exact INSERT SaveItems builds, with durability persisted
q("INSERT INTO cq_item (account_id, item_type, sort, amount, position, name, plus, durability) "
  "VALUES (99003, 410051, 1, 1, 1, 'Blade', 2, 850)")
row = q("SELECT item_type, plus, durability FROM cq_item WHERE account_id=99003")
assert row == "410051\t2\t850", row
q("DELETE FROM cq_item WHERE account_id=99003")
print("DUR_SQL_OK: cq_item round-trips durability 850")
