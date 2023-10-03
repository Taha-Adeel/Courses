CREATE VIEW paper_citations_cliques AS
SELECT DISTINCT LEAST(c1.cited_by, c2.cited_by, c2.cited) as A, c1.cited_by + c2.cited_by + c2.cited - LEAST(c1.cited_by, c2.cited_by, c2.cited) - GREATEST(c1.cited_by, c2.cited_by, c2.cited) as B, GREATEST(c1.cited_by, c2.cited_by, c2.cited) as C
FROM citations c1 join citations c2 on c2.cited_by = c1.cited
WHERE EXISTS (SELECT *
            FROM citations c3
            WHERE (((c3.cited_by = c1.cited_by) AND (c3.cited = c2.cited)) OR ((c3.cited_by = c2.cited) AND (c3.cited = c1.cited_by))));

CREATE VIEW author_citation_cliques AS
SELECT LEAST(a1.author_id, a2.author_id, a3.author_id) as X, a1.author_id + a2.author_id + a3.author_id - LEAST(a1.author_id, a2.author_id, a3.author_id) - GREATEST(a1.author_id, a2.author_id, a3.author_id) as Y, GREATEST(a1.author_id, a2.author_id, a3.author_id) as Z, COUNT(*) as count
FROM paper_citations_cliques p join auth_paper a1 on p.a = a1.paper_index
                        join auth_paper a2 on p.b = a2.paper_index
                        join auth_paper a3 on p.c = a3.paper_index
WHERE a1.author_id != a2.author_id AND a2.author_id!=a3.author_id AND a3.author_id!=a1.author_id
GROUP BY (X, Y, Z);

SELECT a.author_id as x_id, a.first_name || ' ' || a.middle_name || ' ' || a.last_name as x_name,
        b.author_id as y_id, b.first_name || ' ' || b.middle_name || ' ' || b.last_name as y_name,
        c.author_id as z_id, c.first_name || ' ' || c.middle_name || ' ' || c.last_name as z_name,
        cit.count as count
INTO query6
FROM author_citation_cliques cit join authors a on cit.x = a.author_id
                                join authors b on cit.y = b.author_id
                                join authors c on cit.z = c.author_id;
