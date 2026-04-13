import re
import pandas as pd
print("Project 3 for CS 341\nSection number: H02\nSemester: Spring 2026\nWritten by: Arda Ayna, aa3755\nInstructor: Marvin Nakayama, marvin@njit.edu\n")


def process755():
    case_count = input("Enter the number of encoded problem instances to process (m>=0): \n")
    try:
        case_count = int(case_count)
    except ValueError:
        print("This is not a valid input.\n")
        return 1
    if case_count == 0:
        print("No input to process.\n")
        return 0
    elif case_count < 0:
        print("case_count cannot be negative.\n")
        return 1
    
    print(f"The number of encoded problem instances to process: {case_count}")
    for i in range(1,case_count+1):
        case = input(f"Enter encoded problem instance {i} of {case_count}: \n")
        #using regex to match the input to the required format.
        regex = r"^(#*)(\{(?:q[0-9]+,)*q[0-9]+\}),(\{(?:(?:.,)*.)?\}),(\$*),(\{(?:(?:\(q[0-9]+:.:q[0-9]+\),)*\(q[0-9]+:.:q[0-9]+\))?\}),(q[0-9]+),(\{(?:q[0-9]+,)*q[0-9]+\})(&*)$"
        """
        Because this regex is extremely long, here is a breakdown:
            ^(#*) - matches the #'s from the beginning of the line and puts them into character class 1, ensuring no characters exist before #'s in the line.
            (\{(?:q[0-9]+,)*q[0-9]+\}) - matches the set of states and puts them into character class 2.
            (\{(?:(?:.,)*.)?\}) - matches the symbols in the input alphabet and puts them into character class 3.
            (\$*) matches $'s into character class 4.
            (\{(?:(?:\(q[0-9]+:.:q[0-9]+\),)*\(q[0-9]+:.:q[0-9]+\))?\}) - matches the transition function into character class 5.
            (q[0-9]+) - matches the starting state into character class 6.
            (\{(?:q[0-9]+,)*q[0-9]+\}) - matches the set of accepting states into character class 7.
            (&*)$ matches &'s at the end of the line into character class 8, ensuring there are no other characters after.

            Character classes with ?: inside offer the same functionality with the advantage of not being recorded in the character classes and complicating indexing the matched character classes.
            The regex allows for brackets with empty contents because a DFA's language may be empty, implying that there can be no transitions/transition function, even though such a DFA would not be practically useful.

        """
        result = re.findall(regex,case)
        if len(result) == 0:
            print("Invalid encoding\.")
            return 1
        result = result[0]
        pound_length = len(result[0])
        dollar_length = len(result[3])
        ampersand_length = len(result[7])
        if ampersand_length != (pound_length*dollar_length):
            print("Invalid encoding. z!=x*y\n")
            return 1
        #Since regex already split everything up into classes, all that is necessary is to print the classes at the appropriate indices, except for the transition function
        print(f"{result[1]}\n\n")
        print(f"{result[2]}\n\n")
        
        print_transition755(result[1],result[2],result[4])

        print(f"{result[5]}\n\n")
        print(f"{result[6]}\n")
        
def print_transition755(states, language, transition_func):
    states = states[1,len(states)-1]
    states = states.split(',')
    language = language[1,len(language)-1]
    language = language.split(',')
    transition_func = transition_func[1,len(transition_func)-1]
    transition_func = transition_func.split(',')
    



process755()


