SELECT DISTINCT name FROM "people"
JOIN "stars" ON people.id = stars.person_id
JOIN "movies" ON stars.movie_id = movies.id
WHERE movies.title IN(SELECT DISTINCT movies.title FROM "movies"
JOIN "stars" ON stars.movie_id = movies.id
JOIN "people" ON stars.person_id = people.id
WHERE people.name = "Kevin Bacon" AND people.birth = 1958) AND people.name != "Kevin Bacon";