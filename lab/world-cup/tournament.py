# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 100


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file

    filename = sys.argv[1]
    with open(filename) as f:
        reader = csv.DictReader(f)
        for team_whole in reader:
            team_whole["rating"] = int(team_whole["rating"])
            teams.append(team_whole)

            # further understand how list, dictionaies, and csv work. Confused inf [line 24] and
            # [line 25] in regards to how you address certion properties.

            # Once you have a file f, you can use csv.DictReader(f) to give you a “reader”: an
            # object in Python that you can loop over to read the file one row at a time, treating
            # each row as a dictionary.

            # So after it gets turned into a dict team_whole now represents the name of the dictionary
            # and when you call team_whole["rating"] it uses "rating" as the key and returns the value

    print(teams)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts

    for i in range(N):
        winner = simulate_tournament(teams)
        if winner in counts:
            counts[winner] += 1
        else:
            counts[winner] = 1

        # Spelling is important, if the key isnt recognizable then it will automatically add to
        # dictionary with value. Therefore you dont need to appened new items into a empty
        # dictionary

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])
    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO

    while len(teams) > 1:
        teams = simulate_round(teams)
    return teams[0]["team"]

    # In the list it has infromation regarding team name and rating. You only want to return
    # the name. Therefore you do [line 79] to only adress the name.


if __name__ == "__main__":
    main()
