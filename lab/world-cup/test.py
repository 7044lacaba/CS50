team = {
    66 : 'Uruguay',
    'rating': 976
}

print (team[66])
print (team['rating'])

    #the key can only be the left side

counts = {}

winner = "love"

if winner in counts:
    counts[winner] += 1
else:
    counts[winner] = 1

print(counts)
print(counts['love'])