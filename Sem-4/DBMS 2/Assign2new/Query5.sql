CREATE VIEW auth_id_pairs as
SELECT a1.author_id as x, a2.author_id as y,COUNT(*) as count
FROM auth_paper a1 join auth_paper a2 on (a1.paper_index = a2.paper_index AND a1.author_id < a2.author_id)
GROUP BY (x,y);

SELECT a1.author_id as auth1_id, a1.first_name || ' ' || a1.middle_name || ' ' || a1.last_name as auth1_name,
       a2.author_id as auth2_id, a2.first_name || ' ' || a2.middle_name || ' ' || a2.last_name as auth2_name,
       count
INTO query5
FROM auth_id_pairs join authors a1 on auth_id_pairs.x = a1.author_id
                    join authors a2 on auth_id_pairs.y = a2.author_id
WHERE count > 1;
