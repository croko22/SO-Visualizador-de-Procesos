import os

def algorithm_to_mmd(algorithm):
    csv_file = f'data/{algorithm.lower()}.csv'
    mmd_file = f'data/{algorithm.lower()}.mmd'

    with open(csv_file, 'r') as csv, open(mmd_file, 'w') as mmd:
        # Write the MMD header
        # mmd.write(f'---\ndisplayMode: compact\n---\ngantt\ntitle {algorithm} Scheduling\ndateFormat  X\naxisFormat %s\nsection Section\n')
        mmd.write(f'gantt\ntitle {algorithm.upper()} Scheduling\ndateFormat  X\naxisFormat %s\nsection Section\n')

        # Skip the CSV header
        next(csv)
        counter = 0

        for line in csv:
            if counter >= 20:
             break
            
            pid, name, normalized_burst_time, arrival_time, waiting_time, turnaround_time = line.strip().split(',')
            start = int(waiting_time)
            end = int(turnaround_time)
            mmd.write(f'PID {pid} : {start}, {end}\n')

            if waiting_time == '0':
                counter -= 1

            # Increment the counter
            counter += 1

    os.system(f'npx -p @mermaid-js/mermaid-cli mmdc -i {mmd_file} -o data/{algorithm.lower()}.png')

print('Generating Gantt charts...')
algorithm_to_mmd('fcfs')
algorithm_to_mmd('sjf')
algorithm_to_mmd('rr')
print('Done!')