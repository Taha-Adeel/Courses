CREATE VIEW q2_without_authors AS
SELECT p.index as paper_id, c.cited as cited, p2.title as title, p2.venue as venue, p2.year as year
FROM research_papers p LEFT OUTER JOIN (citations c JOIN research_papers p2 on p2.index = c.cited) on p.index = c.cited_by;

SELECT paper_id, cited, title, venue, year, STRING_AGG(a.first_name || ' ' || a.middle_name || ' ' || a.last_name, ', ') as authors
INTO query2
FROM q2_without_authors q LEFT OUTER JOIN (auth_paper JOIN authors a ON auth_paper.author_id = a.author_id) ON q.cited = auth_paper.paper_index
GROUP BY(paper_id, cited, title, venue, year)
ORDER BY paper_id ASC;
