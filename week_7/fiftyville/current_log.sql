-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT name FROM people WHERE phone_number = (
SELECT receiver FROM phone_calls
WHERE year = '2021' AND month = '7' AND day = '28' AND duration < '60' AND caller = '(367) 555-5533');
