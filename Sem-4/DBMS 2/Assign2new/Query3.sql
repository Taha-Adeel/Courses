CREATE VIEW q3_without_authors AS
SELECT p.index as X, c1.cited_by as Z, p2.title as title, p2.venue as venue, p2.year as year
FROM research_papers p LEFT OUTER JOIN (citations c1 JOIN citations c2 on c1.cited = c2.cited_by JOIN research_papers p2 on c1.cited_by = p2.index) on c2.cited = p.index;

SELECT X, Z, title, venue, year, STRING_AGG(a.first_name || ' ' || a.middle_name || ' ' || a.last_name, ', ') as authors
INTO query3
FROM q3_without_authors q LEFT OUTER JOIN (auth_paper JOIN authors a ON auth_paper.author_id = a.author_id) ON q.Z = auth_paper.paper_index
GROUP BY (X, Z, title, venue, year)
ORDER BY X ASC;
