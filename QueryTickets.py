'''
Usage:
    QueryTickets [-gdtkz] <from> <to> <date>

Options:
    -h
    -g
    -d
    -t
    -k
    -z
'''

import re
import ssl
import urllib
import requests
from docopt import docopt
from prettytable import PrettyTable

def GetJson():
    HTML = urllib.urlopen("https://kyfw.12306.cn/otn/resources/js/framework/station_name.js?station_version=1.8955").read()

    Creg = re.compile("([A-Z]+)\|([a-z]+)")
    Stations = re.findall(Creg,HTML)
    
    Stations = dict(Stations)
    Stations = dict(zip(Stations.values(),Stations.keys()))

    arguments = docopt(__doc__)
    FromStation = Stations.get(arguments["<from>"])
    ToStation = Stations.get(arguments["<to>"])
    Date = arguments["<date>"]

    URL = "https://kyfw.12306.cn/otn/lcxxcx/query?purpose_codes=ADULT&queryDate=%s&from_station=%s&to_station=%s" % (Date,FromStation,ToStation)
    
    r = requests.get(URL,verify = False)
    rows = r.json()['data']['datas']
    
    return rows

class ParseData(object):
    def __init__(self,rows):
        self.rows = rows

    def GetDuration(self,row):
        duration = row.get("lishi").replace(":","h") + "m"
        if duration.startswith('00'):
            return duration[4:]
        if duration.startswith('0'):
            return duration[1:]
        return duration
    
    def Trains(self):
        for row in self.rows:
            train = [
                row['station_train_code'],
                '\n'.join([row['start_station_name'], row['end_station_name']]),
                '\n'.join([row['start_time'], row['arrive_time']]),
                self.GetDuration(row),
                row['zy_num'],
                row['ze_num'],
                row['rw_num'],
                row['yw_num'],
                row['yz_num']
            ]
            yield train

    def PrintData(self):
        header = 'train station time duration first second softsleep hardsleep hardsit'.split()

        pt = PrettyTable()
        pt._set_field_names(header)
        for train in self.Trains():
            pt.add_row(train)
        print(pt)

ssl._create_default_https_context = ssl._create_unverified_context

trains = ParseData(GetJson())
trains.PrintData()

