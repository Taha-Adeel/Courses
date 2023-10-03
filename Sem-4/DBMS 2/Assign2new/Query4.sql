SELECT cited, COUNT(*) as count
INTO Query4
FROM citations c
GROUP BY cited
ORDER BY count DESC
LIMIT 20;
