import subprocess
def q(sql):
    r = subprocess.run(["mariadb", "-u", "tqserver", "-ptqpass123", "tqserver", "-N", "-e", sql],
                       capture_output=True, text=True)
    if r.returncode != 0:
        print("SQL FAILED:", r.stderr.strip()); raise SystemExit(1)
    return r.stdout.strip()

# 1) realms exist and the CCrossClient identity query works per server id
row = q("SELECT name FROM cq_realm WHERE id=1")
assert row == "TwinRealm", row
row = q("SELECT name FROM cq_realm WHERE id=2")
assert row == "MoonRealm", row

# 2) the exact JOIN SpawnCrossFromDB runs: cols map_id,count,x,y,respawn,cp,name,level,life,attack,defense
rows = q("SELECT c.map_id, c.count, c.x, c.y, c.respawn_secs, c.cp_reward, t.name, t.level, t.life, t.attack, t.defense "
         "FROM cq_cross_monster c JOIN cq_monstertype t ON t.id = c.type_id").split("\n")
assert len(rows) == 2, rows
first = rows[0].split("\t")
assert first[0] == "1002" and first[1] == "2", first     # map + count
assert first[4] == "300" and first[5] == "25", first      # respawn secs + CP bounty
second = rows[1].split("\t")
assert second[1] == "1" and second[5] == "50", second     # 1 Bandit, 50 CP

# 3) respawn cadence math the server uses (AI tick = 2s): 300s -> 150 ticks, 600s -> 300
r1 = int(first[4]) // 2
r2 = int(second[4]) // 2
assert r1 == 150 and r2 == 300

# 4) orphan type_id (dangling reference) must not break the JOIN loader: it is skipped
q("INSERT INTO cq_cross_monster (type_id, map_id, count, x, y) VALUES (999999, 1002, 1, 500, 500)")
rows = q("SELECT c.map_id, c.count, c.x, c.y, c.respawn_secs, c.cp_reward, t.name, t.level, t.life, t.attack, t.defense "
         "FROM cq_cross_monster c JOIN cq_monstertype t ON t.id = c.type_id").split("\n")
assert len(rows) == 2, "orphan must vanish from the JOIN: " + str(rows)
q("DELETE FROM cq_cross_monster WHERE type_id=999999")

print("REALM_SQL_OK: cq_realm identities, cross JOIN shape, CP bounties, respawn cadence math, orphan resilience")
