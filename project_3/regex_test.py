import re
import tabulate

regex = r"^(#*)(\{(?:q[0-9]+,)*q[0-9]+\}),(\{(?:(?:.,)*.)?\}),(\$*),(\{(?:(?:\(q[0-9]+:.:q[0-9]+\),)*\(q[0-9]+:.:q[0-9]+\))?\}),(q[0-9]+),(\{(?:q[0-9]+,)*q[0-9]+\})(&*)$"
testcase = "##{q0,q1,q2},{a,b},$,{(q0:a:q0),(q0:b:q1),(q1:a:q1),(q1:b:q0),(q2:a:q1),(q2:b:q0)},q0,{q2}&&"
result= (re.findall(regex,testcase))[0]
print(result)

def print_transition755(states, language, transition_func):
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
    print(tabulate.tabulate(data,headers=header))

print_transition755(result[1],result[2],result[4])