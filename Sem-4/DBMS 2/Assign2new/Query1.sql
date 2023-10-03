CREATE VIEW q1_without_authors AS
SELECT p.index as paper_id, c.cited_by as cited_by, p2.title as title, p2.venue as venue, p2.year as year
FROM research_papers p LEFT OUTER JOIN (citations c JOIN research_papers p2 on p2.index = c.cited_by) on p.index = c.cited;

SELECT paper_id, cited_by, title, venue, year, STRING_AGG(a.first_name || ' ' || a.middle_name || ' ' || a.last_name, ', ') as authors
INTO Query1
FROM q1_without_authors q LEFT OUTER JOIN (auth_paper JOIN authors a ON auth_paper.author_id = a.author_id) ON q.cited_by = auth_paper.paper_index
GROUP BY(paper_id, cited_by, title, venue, year)
ORDER BY paper_id ASC;
