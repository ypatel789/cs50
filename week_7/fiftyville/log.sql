-- Keep a log of any SQL queries you execute as you solve the mystery.

-- To find description of the crime scene report of when the crime happened
SELECT description FROM crime_scene_reports
WHERE street = 'Humphrey Street' AND year = '2021' AND month = '7' AND day = '28';

-- To find the interview transcripts that mention bakery
SELECT transcript FROM interviews
WHERE year = '2021' AND month = '7' AND day = '28' AND transcript LIKE '%bakery%';

-- To find license plates of cars that left bakery within 10 minutes of theft occuring
SELECT license_plate FROM bakery_security_logs
WHERE year = '2021' AND month = '7' AND day = '28' AND hour = '10' AND minute < '25' AND activity = 'exit';

-- To find list of names of people who are registered to the cars that exited the bakery at said time in first interview
SELECT name FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE year = '2021' AND month = '7' AND day = '28' AND hour = '10' AND minute >= '15' AND minute <= '25' AND activity = 'exit';

-- To find list of people who withdrew money from legget street on the day of the robbery
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = '2021' AND month = '7' AND day = '28' AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street';

-- To find name of passengers on the earliest flight out of Fiftyville on the 29 Jul 2021
SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = (
SELECT id FROM flights
WHERE year = '2021' AND month = '7' AND day = '29' AND origin_airport_id = (
SELECT id FROM airports WHERE city = 'Fiftyville')
ORDER BY hour,minute
LIMIT 1);

-- To find name of people who made a phone call on the day of the robbery that lasted less than 1 minute
SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE year = '2021' AND month = '7' AND day = '28' AND duration < '60';

-- Where did they escape to
SELECT city FROM airports
WHERE id = (SELECT destination_airport_id FROM flights
WHERE year = '2021' AND month = '7' AND day = '29' AND origin_airport_id = (
SELECT id FROM airports WHERE city = 'Fiftyville')
ORDER BY hour, minute
LIMIT 1);

-- What is Bruces phone number
SELECT phone_number FROM people WHERE name = 'Bruce';

-- Who was the accomplice
SELECT name FROM people WHERE phone_number = (
SELECT receiver FROM phone_calls
WHERE year = '2021' AND month = '7' AND day = '28' AND duration < '60' AND caller = '(367) 555-5533');
