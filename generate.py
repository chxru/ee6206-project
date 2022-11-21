import csv
import random


def normalizeFloat(value):
    # add leading zero if below 10 and add zero to end if one decimal
    if value < 10:
        value = "0" + str(value)
    else:
        value = str(value)
    if len(value.split(".")[1]) == 1:
        value = value + "0"
    return value


with open("data.csv", "w") as csv_file:
    writer = csv.writer(csv_file, delimiter=',')
    for line in range(0, 100):
        idx = 'EG/201' + str(random.randint(1, 9)) + '/' + \
            str(random.randrange(1000, 9999))

        as1 = normalizeFloat(round(random.uniform(5, 15), 2))
        as2 = normalizeFloat(round(random.uniform(5, 15), 2))
        prj = normalizeFloat(round(random.uniform(5, 20), 2))
        fnl = normalizeFloat(round(random.uniform(5, 50), 2))

        writer.writerow([idx, as1, as2, prj, fnl])
