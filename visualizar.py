import plotly.express as px
import pandas as pd

# Data provided
data = {
    'pid': [1, 2, 3, 4, 5, 6, 7, 9],
    'start_time': [0, 4204211, 8408422, 12612633, 16816844, 21021055, 25225266, 29429477],
    'end_time': [4204211, 8408422, 12612633, 16816844, 21021055, 25225266, 29429477, 33633688]
} 

df = pd.DataFrame(data)

# Create Gantt chart using Plotly
fig = px.timeline(df, x_start='start_time', x_end='end_time', y='pid', labels={'pid': 'Process ID'},
                  title='Gantt Chart for Process Execution',
                  category_orders={'pid': sorted(df['pid'], reverse=True)})

# Show Gantt chart
fig.update_yaxes(categoryorder='total ascending')
fig.write_html('first_figure.html', auto_open=True)
# fig.show()
