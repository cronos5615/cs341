import re
import tabulate
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
        print("Case count cannot be negative.\n")
        return 1
    
    print(f"The number of encoded problem instances to process: {case_count}\n")
    for i in range(1,case_count+1):
        #without strip, this is unable to process files written on windows devices because \r that windows encoding adds does not match the regex
        case = input(f"Enter encoded problem instance {i} of {case_count}: \n").strip("\r")
        print(f"The problem instance to process is: {case}\n")
        #using regex to match the input to the required format.
        regex = r"^(#*)(\{(?:q[0-9]+,)*q[0-9]+\}),(\{(?:(?:.,)*.)?\}),(\$*),(\{(?:(?:\(q[0-9]+:.:q[0-9]+\),)*\(q[0-9]+:.:q[0-9]+\))?\}),(q[0-9]+),(\{(?:q[0-9]+,)*q[0-9]+\})(&*)$"
        r"""
        Because this regex is extremely long, here is a breakdown:
            ^(#*) - matches the #'s from the beginning of the line and puts them into character class 1, ensuring no characters exist before #'s in the line.
            (\{(?:q[0-9]+,)*q[0-9]+\}) - matches the set of states and puts them into character class 2.
            (\{(?:(?:.,)*.)?\}) - matches the symbols in the input alphabet and puts them into character class 3.
            (\$*) matches $'s into character class 4.
            (\{(?:(?:\(q[0-9]+:.:q[0-9]+\),)*\(q[0-9]+:.:q[0-9]+\))?\}) - matches the transition function into character class 5.
            (q[0-9]+) - matches the starting state into character class 6.
            (\{(?:q[0-9]+,)*q[0-9]+\}) - matches the set of accepting states into character class 7.
            (&*)$ matches &'s at the end of the line into character class 8, ensuring there are no other characters after.

            Character classes with "?:" inside offer the same functionality with the advantage of not being recorded in the character classes list and complicating indexing the matched character classes.
            The regex allows for brackets with empty contents because a DFA's language may be empty, implying that there can be no transitions/transition function, even though such a DFA would not be practically useful.

        """
        result = re.findall(regex,case)
        if len(result) == 0:
            print("Invalid encoding.\nRejected.\n")
            return 1
        result = result[0]
        pound_length = len(result[0])
        dollar_length = len(result[3])
        ampersand_length = len(result[7])
        if ampersand_length != (pound_length*dollar_length):
            print("Invalid encoding. z!=x*y\nRejected.\n")
            continue
        #Since regex already split everything up into classes, all that is necessary is to print the classes at the appropriate indices, except for the transition function
        print(f"States: {result[1]}\n")
        print(f"Language: {result[2]}\n")
        
        print("Transition function:\n")
        transtion_dict = print_transition755(result[1],result[2],result[4])
        print("\n")

        print(f"Starting state: {result[5]}\n")
        print(f"Accept states: {result[6]}\n")

        #emptiness problem solution starts here
        states = result[1][1:len(result[1])-1].split(",")
        accept_states = result[6][1:len(result[6])-1].split(",")
        reachable_states = set([result[5]])
        for i in range(len(states)):

            for key,value in transtion_dict.items():
                #going over the dictionary that was used in the print function. key[0] is the current stage, key[1] is the symbol read, which does not matter here.
                if((key[0] in reachable_states) and (value not in reachable_states) ):
                    reachable_states.add(value)
            print(f"The reachable states are after iteration {i+1} are:\n{reachable_states}\n")
        if(any(item in accept_states for item in reachable_states)):
                print("Rejected\n")
                continue
        print("Accepted\n")


def print_transition755(states, language, transition_func):
    #setting up states, language, and transition func by turning them into lists from strings.
    states = states[1:len(states)-1]
    states = states.split(',')
    language = language[1:len(language)-1]
    language = language.split(',')
    transition_func = transition_func[1:len(transition_func)-1]
    transition_func = transition_func.split(',')
    
    transition_dict = {}
    for transition in transition_func:
        transition = transition[1:len(transition)-1].split(":")
        q_from,symbol,q_to = transition
        transition_dict[(q_from,symbol)] = q_to
    
    header = ["State"]+language

    data = []
    for state in states:
        row = [state]
        for symbol in language:
            row.append(transition_dict[(state,symbol)])
        data.append(row)
    print(tabulate.tabulate(data,headers=header,tablefmt="github"))
    #this is setting up for the emptiness problem solution because my solution uses this dictionary
    return transition_dict





process755()


