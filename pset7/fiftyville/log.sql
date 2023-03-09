-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check what tables we have access to
.table

-- Check what imputs can fit into the table crime_scene_reports
.schema crime_scene_reports

-- Input what was provided into a select query
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

-- Check what imputs can fit into the table interview
.schema interviews

-- Check times disclosed in interviews
SELECT * FROM interviews WHERE month = 7 AND day = 28 AND year = 2021;

-- Check what imputs can fit into the table bakery_security_logs
.schema bakery_security_logs

-- Check time frame for plates coming in and out
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 and 25;

-- Check atm transactions
.schema atm_transactions

-- Plug in time to check atm transactions
SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

-- Check for the first flight on the next day
SELECT * FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour ASC, minute ASC;

-- Check what info can be put into the table airports
SELECT * FROM airports;

-- Check phone calls around the proper time fram and duration under 60 mins
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- Check for account numbers that are on proper day
SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

-- Cross check everything to get phone numbers
SELECT id FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 and 25) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- Cross check to get a name
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.person_id IN (SELECT id FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 and 25) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36))
AND bank_accounts.account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw");

-- User name to find partner
SELECT name from people
WHERE phone_number = (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (SELECT phone_number FROM people WHERE name = "Bruce"));
