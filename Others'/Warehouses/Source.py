import copy
import csv
import random
import sys
import time


space_per_unit = 0.0332
crossover_rate = 0.4
mutation_rate = 0.2
percent_elitism = 0.4

best_indiv_gen_no = 0
best_indiv_cost_val = sys.maxsize


class WareHouse(object):
    def __init__(self, d, name='Unnamed'):
        self.name = str(name)

        self.AS = int(d['avail_space'])
        self.quantity = int(d['demand'])
        self.demand = int(d['demand'])

        self.LCost = int(d['unload_cost'])
        self.HCost = sum(int(cost) for cost in [d['maintenance_cost'], d['utility_cost'], d['labour_cost']])
        self.TCost = int(d['unit_truck_cost']) / 200
        self.OCost = int(d['ordering_cost'])

        self.LConstr = int(d['unld_constr'])
        self.HConstr = int(d['hld_constr'])
        self.TConstr = int(d['trns_constr'])
        self.OConstr = int(d['ord_constr'])
        c1 = self.LConstr // self.LCost
        c2 = self.HConstr // self.HCost
        c3 = self.TConstr // self.TCost
        c4 = self.OCost // self.OConstr
        self.min_Q = max(c1, c2, c3, c4)
        self.max_Q = min(self.demand, int(self.AS // space_per_unit))

    def show_warehouse_info(self):
        print('Warehouse: {}\nAvailable Space: {}\n'.format(self.name, self.AS))

        print('{:25}{:>7}'.format('Cost type', 'Cost'))
        print('{:->32}'.format(''))
        print('{:25}{:>7}'.format('Loading Cost', self.LCost))
        print('{:25}{:>7}'.format('Holding Cost', self.HCost))
        print('{:25}{:>7}'.format('Transportation Cost', self.TCost))
        print('{:25}{:>7}\n'.format('Ordering Cost', self.OCost))

        print('{:25}{:>7}'.format('Constraint type', 'Factor'))
        print('{:->32}'.format(''))
        print('{:25}{:>7}'.format('Loading Constraint', self.LConstr))
        print('{:25}{:>7}'.format('Holding Constraint', self.HConstr))
        print('{:25}{:>7}'.format('Transportation Constraint', self.TConstr))
        print('{:25}{:>7}'.format('Ordering Constraint', self.OConstr))

        print('Minimum Q: {}'.format(self.min_Q))
        print('Maximum Q: {}'.format(self.max_Q))

    def setQ(self, newQ):
        self.quantity = newQ

    def __str__(self):
        return self.name + ': ' + str(self.quantity)


def cost_warehouse(wh):
    cost = wh.quantity * (wh.LCost + wh.HCost + wh.TCost) + (wh.OCost / wh.quantity)
    return cost


def cost_total(indiv):
    sumcost = sum(cost_warehouse(wh) for wh in indiv)
    return sumcost


def fitness(warehouses):
    fitness_val = 1 / cost_total(warehouses)
    return fitness_val

def create_warehoues_from_input():
    warehouses = []
    with open('input.csv') as csvfile:
        reader = csv.DictReader(csvfile)
        for i, row in enumerate(reader):
            warehouses.append(WareHouse(row, name=i + 1))

    return warehouses


def create_population(init_indiv, n):
    population = []
    for i in range(n):
        ind = []
        for j, wh in enumerate(init_indiv):
            new_wh = copy.deepcopy(wh)
            min_q, max_q = wh.min_Q, wh.max_Q
            new_wh.setQ(random.randint(min_q, max_q))
            ind.append(new_wh)
        population.append(ind)

    return sorted_population(population)


def print_wh(warehouses, gen_no):
    print_chunks = ['{:10}'.format(str(wh)) for wh in warehouses]
    wh_cost = int(cost_total(warehouses))
    print_chunks.append('[{}]'.format(wh_cost))
    ret_str = ''.join(print_chunks)

    global best_indiv_cost_val, best_indiv_gen_no
    if wh_cost < best_indiv_cost_val:
        best_indiv_gen_no = gen_no
        best_indiv_cost_val = wh_cost

    return ret_str


def print_pop(population, gen_no):
    print_lines = ['Generation: {}'.format(gen_no)]
    print_lines += [print_wh(indiv, gen_no) for indiv in population]
    print_lines.append('\n')
    ret_str = '\n'.join(print_lines)

    return ret_str


def print_best_avg(population, gen_no):
    print_lines = ['Generation: {}'.format(gen_no)]
    print_lines.append('Best in this generation: {}'.format(int(cost_total(population[0]))))
    avg = sum(cost_total(indiv) for indiv in population) / len(population)
    print_lines.append('Average in this generation: {}'.format(avg))
    print_lines.append('\n')
    ret_str = '\n'.join(print_lines)

    return ret_str


def print_time_results(start_time, end_time):
    print_lines = ['Best value: {}'.format(best_indiv_cost_val)]
    print_lines.append('Elapsed time: {}s'.format(end_time-start_time))
    print_lines.append('Best solution found at generation: {}'.format(best_indiv_gen_no))
    ret_str = '\n'.join(print_lines)

    return ret_str


def sorted_population(population):
    population.sort(key=cost_total)
    return population


def roulette_selection(population):
    elite_count = get_elite_count(population)

    probabilities = []
    total_fitness = sum(fitness(indiv) for indiv in population[elite_count:])

    probabilities.append(fitness(population[elite_count]) / total_fitness)
    for i in range(elite_count+1, len(population), 1):
        probabilities.append(probabilities[-1] + fitness(population[i]) / total_fitness)

    if probabilities[-1] > 1.0:
        probabilities[-1] = 1

    new_pop = copy.deepcopy(population[:elite_count])

    for i in range(len(population) - elite_count):
        rand = random.random()
        for j, indiv in enumerate(population[elite_count:]):
            if rand <= probabilities[j]:
                new_pop.append(copy.deepcopy(indiv))
                break

    return sorted_population(new_pop)


def get_elite_count(population):
    return int(percent_elitism * len(population))


def crossover(population):
    elite_count = get_elite_count(population)

    def choose_indices(c1, c2):
        length = len(c1)
        partition_mark = random.randrange(1, length-1)
        idx1 = random.randrange(0, partition_mark)
        idx2 = random.randrange(partition_mark, length)

        return min(idx1, idx2), max(idx1, idx2)

    def cross(c1, c2):
        idx1, idx2 = choose_indices(c1, c2)
        temp = copy.deepcopy(c1[idx1:idx2])
        c1[idx1:idx2] = copy.deepcopy(c2[idx1:idx2])
        c2[idx1:idx2] = temp

        return c1, c2

    chosen = []
    for i in range(len(population)-elite_count):
        if random.random() <= crossover_rate:
            chosen.append(i+elite_count)
    if len(chosen) % 2 == 1:
        chosen = chosen[:-1]

    for i in range(0, len(chosen), 2):
        offsprings = cross(population[chosen[i]], population[chosen[i + 1]])
        population[chosen[i]] = offsprings[0]
        population[chosen[i+1]] = offsprings[1]

    return sorted_population(population)


def mutation(population):
    elite_count = get_elite_count(population)
    def mutate(wh):
        randval = random.randint(wh.min_Q, wh.max_Q)
        wh.setQ(randval)
        return wh

    for i, indiv in enumerate(population[elite_count:]):
        for j, wh in enumerate(indiv):
            if random.random() <= mutation_rate:
                population[i+elite_count][j] = mutate(wh)

    return sorted_population(population)


def evolve(population, times):
    all_gen_results_file = open('All generation results.txt', 'w')
    best_avg_results_file = open('Best and average results.txt', 'w')
    time_results_file = open('Time for best solution.txt', 'w')

    start = time.time()
    print('Running', end='', flush=True)
    for i in range(times):
        if i % (times//7) == 0:
            print('.', flush=True, end='')

        population = roulette_selection(population)
        population = crossover(population)
        population = mutation(population)

        all_gen_results_file.write(print_pop(population, i+1))
        best_avg_results_file.write(print_best_avg(population, i+1))

    end = time.time()

    all_gen_results_file.close()
    best_avg_results_file.close()

    time_results_file.write(print_time_results(start, end))
    time_results_file.close()
    print('Complete!')
    print('3 files created:\n')
    print('"All generation results.txt"')
    print('"Best and average results.txt"')
    print('"Time for best solution.txt"')

if __name__ == '__main__':
    init_indiv = create_warehoues_from_input()

    num_of_indiv = int(input('Enter the size of initial population: '))

    percent_elitism = float(input('Enter elitism fraction (0-1): '))
    assert 0 < percent_elitism < 1

    crossover_rate = float(input('Enter crossover rate (0-1): '))
    assert 0 < crossover_rate < 1

    mutation_rate = float(input('Enter mutation rate (0-1): '))
    assert 0 < mutation_rate < 1

    num_of_epoch = int(input('Enter number of epoch to run: '))

    # num_of_indiv = 10
    # num_of_epoch = 100
    population = create_population(init_indiv, num_of_indiv)

    evolve(population, num_of_epoch)
