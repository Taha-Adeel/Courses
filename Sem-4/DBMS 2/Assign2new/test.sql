SELECT venue, COUNT(*) as count
INTO test
FROM research_papers JOIN auth_paper on auth_paper.paper_index = research_papers.index
GROUP BY venue
ORDER BY venue DESC
