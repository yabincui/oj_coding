# Write your MySQL query statement below
WITH PeopleInOrder AS (
    -- First, calculate the cumulative weight for each person in the queue
    SELECT
        person_name,
        turn,
        SUM(weight) OVER (ORDER BY turn) as cumulative_weight
    FROM
        Queue
)
-- Then, from the people who can fit, select the one with the highest turn number
SELECT
    person_name
FROM
    PeopleInOrder
WHERE
    cumulative_weight <= 1000
ORDER BY
    turn DESC
LIMIT 1;