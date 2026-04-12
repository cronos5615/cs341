import re
print("Project 3 for CS 341\nSection number: H02\nSemester: Spring 2026\nWritten by: Arda Ayna, aa3755\nInstructor: Marvin Nakayama, marvin@njit.edu\n")


def process():
    case_count = input("Enter the number of encoded problem instances to process (m>=0): \n")
    try:
        case_count = int(case_count)
    except ValueError:
        print("This is not a valid input.\n")
        return
    if case_count == 0:
        print("No input to process.\n")
        return
    elif case_count < 0:
        print("case_count cannot be negative.\n")
        return
    
    print(f"The number of encoded problem instances to process: {case_count}")
    for i in range(1,case_count+1):
        case = input(f"Enter encoded problem instance {i} of {case_count}: \n")
        #using regex to match the input to the required format.
        case = case.strip()
        regex = "^(#*)(\{(q\[0-9\]+,)*q\[0-9\]\}),\{((.,)*.)?\},\$*"


process()


