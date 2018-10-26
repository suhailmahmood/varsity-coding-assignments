import csv
import random
from copy import deepcopy

taboo_list = []
initial_generation = []


class Job:
    def __init__(self, name, op_list):
        self.name = name
        self.op_list = {}
        self.idx = {}
        for k, v in op_list.items():
            # self.op_list[k] = sorted(v, key=lambda tup: tup[1])
            self.op_list[k] = op_list[k]
            self.idx[k] = 0

    def next_min(self, op):
        if self.idx[op] < len(self.op_list[op]):
            return_val = self.op_list[op][self.idx[op]]
            self.idx[op] += 1
        else:
            return_val = self.op_list[op][-1]
        return return_val

    def has_next(self, op):
        if self.idx[op] < len(self.op_list[op]):
            return True
        return False

    def reset_idx(self):
        for k, v in self.idx.items():
            self.idx[k] = -1

    def __str__(self):
        return str(self.name)


def read_file():
    with open('input.csv', newline='') as file:
        reader = csv.reader(file)

        schedule = {}
        for row in reader:
            job, op, mach, time = int(row[0]), int(row[1]), int(row[2]), int(row[3])
            if job not in schedule:
                schedule[job] = {op: [(mach, time)]}
            else:
                if op not in schedule[job]:
                    schedule[job][op] = [(mach, time)]
                else:
                    schedule[job][op].append((mach, time))

    return schedule


def create_jobs(schedule):
    jobs = [Job(job_name, op_list) for job_name, op_list in schedule.items()]
    return jobs


def create_initial_generation(jobs):
    rows = []
    op_available = True
    first_row = True

    while op_available:
        anyone_changed = False
        change_idx = 0
        row = []

        for i, job in enumerate(jobs):

            for j, (op, mach_time) in enumerate(job.op_list.items()):
                if first_row:
                    next_min_op = job.next_min(op)
                    row.append((job, op, next_min_op[0]))

                elif not anyone_changed:
                    new_job = deepcopy(rows[-1][change_idx])[0]
                    if new_job.has_next(op):

                        next_min_op = new_job.next_min(op)
                        row.append((new_job, op, next_min_op[0]))
                        change_idx += 1

                        anyone_changed = True
                    else:
                        row.append(deepcopy(rows[-1][change_idx]))
                        change_idx += 1
                else:
                    row.append(deepcopy(rows[-1][change_idx]))
                    change_idx += 1

        first_row = False
        change_idx += 1

        if rows and equal_rows(row, rows[-1]):
            op_available = False
        else:
            rows.append(row)
            insert_in_taboo_list(row)

    return rows


def create_new_generation(generation):
    new_generation = []

    for i, row in enumerate(generation):
        new_row = deepcopy(row)

        trial = 0
        while trial < 5:
            rand_idx = random.randrange(len(new_row))
            job, op, mach = new_row[rand_idx]
            if job.has_next(op):
                new_row[rand_idx] = (job, op, job.next_min(op)[0])
                break
            else:
                trial += 1

        new_generation.append(new_row)
        insert_in_taboo_list(new_row)

    return new_generation


def insert_in_taboo_list(row):
    if not any(equal_rows(row, taboo_row) for taboo_row in taboo_list):
        taboo_list.append(row)
        return True
    return False


def equal_rows(row1, row2):
    if any(str(tup1[0]) != str(tup2[0]) or tup1[1:] != tup2[1:] for tup1, tup2 in zip(row1, row2)):
        return False
    return True


def calc_row_time(row):
    row_time = 0
    for job, op, mach in row:
        for tup in job.op_list[op]:
            if tup[0] == mach:
                row_time += tup[1]

    return row_time


def calc_gen_time(generation):
    return sum(calc_row_time(row) for row in generation)


def show_row(row):
    row_time = calc_row_time(row)
    for tup in row:
        print('({job}, {op}, {m})'.format(job=tup[0], op=tup[1], m=tup[2]), end='')

    print(' --> {}'.format(row_time))


def show_generation(generation, n=''):
    print('Generation {}'.format(n))
    gen_time = 0
    for row in generation:
        row_time = calc_row_time(row)
        gen_time += row_time
        for tup in row:
            print('({job}, {op}, {m})'.format(job=tup[0], op=tup[1], m=tup[2]), end='')
        print(' --> {}'.format(row_time))

    print('Generation time: {}'.format(gen_time))


def show_minimum():
    min_time = calc_row_time(taboo_list[0])
    min_row = taboo_list[0]
    for row in taboo_list:
        calc_time = calc_row_time(row)
        if calc_time < min_time:
            min_row = row
            min_time = calc_time

    show_row(min_row)
    print('Minimum time: {}'.format(min_time))


def evolve(init_generation, times):
    for i in range(times):
        if i % (times // 5) == 0:
            gen = create_new_generation(init_generation)

        gen = create_new_generation(gen)
        show_generation(gen, n=i + 1)
        print()

    print('\n\nTaboo list size:', len(taboo_list))
    print('\nMinimum combination from taboo list:')
    show_minimum()


if __name__ == '__main__':
    schedule = read_file()

    jobs = create_jobs(schedule)

    initial_generation = create_initial_generation(jobs)

    evolve(initial_generation, 300)
