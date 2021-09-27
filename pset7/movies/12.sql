SELECT movies.title AS title FROM "movies"
JOIN "stars" ON stars.movie_id = movies.id
JOIN "people" ON stars.person_id = people.id
WHERE people.name = "Johnny Depp"
INTERSECT
SELECT movies.title AS title FROM "movies"
JOIN "stars" ON stars.movie_id = movies.id
JOIN "people" ON stars.person_id = people.id
WHERE people.name = "Helena Bonham Carter";