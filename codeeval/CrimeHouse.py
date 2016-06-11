import sys

class Status(object):
    def __init__(self, in_house, event_pos):
        self.in_house = in_house
        self.event_pos = event_pos

class Mask(object):
    def __init__(self, is_mask, action):
        self.is_mask = is_mask
        self.action = action
        self.used = False

def judgeEvents(events):
    """Return min number of people in the house if it is possible only having one entry,
    otherwise return -1"""
    mask_array = []
    for event in events:
        mask_array.append(Mask(event[1] == 0, event[0]))

    last_count_array = [0 for x in range(len(events))]

    status_set = {}
    for i in range(len(events)):
        event = events[i]
        action = event[0]
        number = event[1]
        if number != 0:
            if action == 'E':
                # It is the first time appear, or it has left before, or a mask is left before
                if not status_set.has_key(number):
                    status_set[number] = Status(True, i)
                elif status_set[number].in_house == False:
                    status_set[number] = Status(True, i)
                else:
                    # Find a leave mask nearest to the enter event.
                    j = status_set[number].event_pos + 1
                    while j < i:
                        if mask_array[j].is_mask and mask_array[j].action == 'L' and \
                                not mask_array[j].used:
                            break
                        j += 1
                    if j == i:
                        return -1
                    mask_array[j].used = True
                    status_set[number] = Status(True, i)
            else:
                # It is the first time appear, or it has entered before, or a mask is entered before
                if not status_set.has_key(number):
                    status_set[number] = Status(False, i)
                    # we can make it consume a mask enter action if possible.
                    last_count_array[i] = -1
                elif status_set[number].in_house == True:
                    status_set[number] = Status(False, i)
                else:
                    # Find an enter mask nearest to the left event.
                    j = status_set[number].event_pos + 1
                    while j < i:
                        if mask_array[j].is_mask and mask_array[j].action == 'E' and \
                                not mask_array[j].used:
                            break
                        j += 1
                    if j == i:
                        return -1
                    mask_array[j].used = True
                    status_set[number] = Status(False, i)

    for i in range(len(events)):
        if mask_array[i].is_mask and not mask_array[i].used:
            if mask_array[i].action == 'E':
                last_count_array[i] = 1
            else:
                last_count_array[i] = -1
    for number in status_set:
        if status_set[number].in_house:
            last_count_array[status_set[number].event_pos] = 1

    result = 0
    #print 'last_count_array = ', last_count_array
    for add in last_count_array:
        if add == -1:
            result = max(0, result - 1)
        elif add == 1:
            result += 1
    return result


with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        test = test.strip()
        if len(test) == 0:
            continue
        (n, events) = test.split(';')
        n = int(n)
        events = events.split('|')
        for i in range(len(events)):
            (action, number) = events[i].split()
            events[i] = (action, int(number))
        result = judgeEvents(events)
        print result if result >= 0 else 'CRIME TIME'
