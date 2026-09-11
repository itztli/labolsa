#!/usr/bin/env python3
#
#    <labolsa> Montecarlo model of market stocks
#    Copyright (C) 2024  Victor De la Luz 
#                        <vdelaluz@enesmorelia.unam.mx>
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
#VERSION Beta (10/22/2024)
#
import mplfinance as mpf
import numpy as np
import pandas as pd
#import matplotlib.pyplot as plt
import re
import datetime
#from matplotlib.pyplot import plot, draw, show
#import matplotlib
#matplotlib.use('gtk4agg')

average = []
Date = []
Open = [] 
High = [] 
Low = [] 
Close = [] 
Volume = []

current_time = datetime.date(2024, 1, 1)
delta = datetime.timedelta(seconds=1)
MAXLINES=1000

#Ibrahm Franch SIGs
#Exploracion Geofisica Erika Olin Solano

with open('test1.dat', 'r') as file:
    renglones = file.readlines()
    lines=0
    for renglon in renglones:
        if renglon.startswith('MEX1'):
            lines=lines+1
            if lines >= MAXLINES:
                break
            line = re.split(r'\s+', renglon.strip())  # Dividir la línea por espacios
            average.append(float(line[3]))
            Date.append(current_time)
            Open.append(float(line[2])) 
            High.append(float(line[5]))
            Low.append(float(line[1]))
            Close.append(float(line[4]))
            Volume.append(0.0)
            current_time += delta
            
#            data.append([carac[0], float(carac[1]), float(carac[2]), float(carac[3]), float(carac[4]), float(carac[5])])  # Datos relevantes de cada columna 

prices = pd.DataFrame({
    'Date': Date,
    'Open': Open,
    'High': High,
    'Low': Low,
    'Close': Close,
    'Volume': Volume
})

prices['Date'] = pd.to_datetime(prices['Date'])  # Asegurarse de que la columna sea datetime

# Establecer el índice como la fecha
prices.set_index('Date', inplace=True)

# Crear el gráfico de velas japonesas
mpf.plot(prices, type='candle', volume=False, style='charles', title='Stock', ylabel='Price')

# columnas importantes 
#columns = ['Code', 'Min', 'Begin', 'Average', 'Close', 'Max']

###DataFrame
##stock_prices = pd.DataFrame(data, columns=columns)
##
###print(stock_prices)  
##

#plt.figure()
#plt.plot(average)

##
### Filtrar las velas que suben y las que bajan
##up = stock_prices[stock_prices.Close >= stock_prices.Begin]
##down = stock_prices[stock_prices.Close < stock_prices.Begin]
##
### Colores
##col_up = 'green'   # Velas hacia arriba
##col_down = 'red'   # Velas hacia abajo
##
### Ancho de las velas
##width = 0.3
##width2 = 0.1
##
### Acciones que suben
##plt.bar(up['Code'], up['Close'] - up['Begin'], width, bottom=up['Begin'], color=col_up)
##plt.bar(up['Code'], up['Max'] - up['Close'], width2, bottom=up['Close'], color=col_up)
##plt.bar(up['Code'], up['Min'] - up['Begin'], width2, bottom=up['Begin'], color=col_up)
##
##
##plt.bar(down['Code'], down['Close'] - down['Begin'], width, bottom=down['Begin'], color=col_down)
##plt.bar(down['Code'], down['Max'] - down['Begin'], width2, bottom=down['Begin'], color=col_down)
##plt.bar(down['Code'], down['Min'] - down['Close'], width2, bottom=down['Close'], color=col_down)
##
##plt.title('Velas Japonesas labolsa')
##plt.xlabel('Code')
##plt.ylabel('Price')
##plt.xticks(rotation=30, ha='right')  # Rotar etiquetas del eje x
##plt.tight_layout()  
##
#plt.show()  
#draw()
#show()
