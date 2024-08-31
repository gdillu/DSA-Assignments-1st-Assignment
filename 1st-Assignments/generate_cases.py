import random

# Function to generate random test cases

def random_test_cases(n):
    test_cases = [random.randint(0, 1000000) for _ in range(n)]
    return "\n".join(map(str, test_cases))

def Best_test_cases(n):
    test_cases = [random.randint(0, 1000000) for _ in range(n)]
    test_cases.sort()
    return "\n".join(map(str, test_cases))

def Worst_test_cases(n):
    test_cases = [random.randint(0, 1000000) for _ in range(n)]
    test_cases.sort(reverse=True)
    return "\n".join(map(str, test_cases))

# Define the sizes you want to generate
sizes = [100, 250, 500,750,1000,2500,5000,7500,10000,25000,50000,75000,100000]

# Generate all test cases and write to a single file
with open("random_all_sizes.txt", "w") as f:
    for size in sizes:
        f.write(f"Test cases for n={size}:\n")
        f.write(random_test_cases(size) + "\n\n")

with open("Best_all_sizes.txt", "w") as f:
    for size in sizes:
        f.write(f"Test cases for n={size}:\n")
        f.write(Best_test_cases(size) + "\n\n")

with open("Worst_all_sizes.txt", "w") as f:
    for size in sizes:
        f.write(f"Test cases for n={size}:\n")
        f.write(Worst_test_cases(size) + "\n\n")
