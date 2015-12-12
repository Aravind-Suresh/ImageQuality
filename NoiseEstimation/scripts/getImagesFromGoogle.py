from bs4 import BeautifulSoup
import requests
import re
import sys

"""
Function to simulate the get requests like the browser
Requires an url of the advanced search format.
Example
https://www.google.co.in/search?as_st=y&tbm=isch&hl=en&as_q=beach&as_epq=&as_oq=&as_eq=&cr=&as_sitesearch=&safe=images&tbs=isz:lt,islt:vga,ic:color,ift:jpg

where
as_q=query - represents the search query indicating that it must contain all the words in the query ( separated by plus (+) )

as_epq=query - represents the exact word search query, the one we use it withing quotes ( also separated by plus (+) for multiple inputs )

as_oq=query - represents the any of these words query ( also separated by plus(+) )

as_eq=query - represents none of these words, the one we use it with minus sign

attributes
->isz:lt - represents "size larger than"
->islt:vga - represents "is larger than vga (640 x 480)"
->ic:color - represents "color, bw"
->ift:jpg  - represents "image format"

The following implements only queries. modify for different attributes
"""


def get_page(url):
    html = requests.get(url).text
    soup = BeautifulSoup(html)
    images = soup.findAll('div', attrs={'class': 'rg_di'})
    link = []
    for div in images:
        l = div.a['href']
        match = re.findall( "imgurl=(.*)(\.[jJ][pP][eE]*[gG])(?:.*)\&imgrefurl", l )
        if( len(match) == 0 ):
            pass
        else:
            m = match[0][0] + match[0][1]
            link.append(m)
#    if len(link) == 1:
#        print match

    return link



queries   = sys.argv[1].split('_')

for i in range( len ( queries ) ):
    if( queries[i] == 'none' ):
        queries[i] = ''
baseurl = "https://www.google.co.in/search?as_st=y&tbm=isch&hl=en&as_q=" + queries[0]+"&as_epq="+queries[1]+"&as_oq=" + queries[2]+"&as_eq=" + queries[3]+"&cr=&as_sitesearch=&safe=images&tbs=isz:lt,islt:vga,ic:color,ift:jpg"+"&tbs=itp:photo"

page = 0
i = 1


list_of_urls = []
flag = 3
f = 0

maxImages = int(queries[-1])
#&biw=1366&bih=334&sei=qqLsU6GUBoK78gX5x4KYCg&ijn=1&ei=qqLsU6GUBoK78gX5x4KYCg&start=100
for i in range(1,maxImages,20):
    url = baseurl + "&ijn=" + str(page) + "&start=" + str(i)
    l = get_page(url)
    if( len(l)==0 ):
        if( f < flag ):
            f = f + 1
            continue
        else:
            print "3 consecutive pages empty. Abort"
            break
    else:
        f = 0

    list_of_urls.extend(l)
 #   if( len(list_of_urls) % 10 == 0 ):
 #       print "Images:%d"%(len(list_of_urls))

# Check for uniqueness of urls
    
assert( len( list_of_urls) != 0 )
#print len(list_of_urls)
unique_urls = set( list_of_urls )
#print len(unique_urls)

#print(len(unique_urls))
for urls in unique_urls:
    print urls.encode('utf-8')
