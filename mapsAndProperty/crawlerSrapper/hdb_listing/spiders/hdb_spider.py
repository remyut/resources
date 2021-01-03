import scrapy

baseURL ='https://www.99.co/singapore/sale/hdb?listing_type=sale&main_category=hdb&map_bounds=1.052315%2C103.357037%2C1.627683%2C104.147485&page_num='
pagination = '1'
endURL = '&property_segments=residential'



print("\'" + baseURL + pagination + endURL + "\'")

class HdbSpider(scrapy.Spider):
    name = "hdb"
    

    def start_requests(self):
        url = "\'" + baseURL + pagination + endURL + "\'"
        urls = [
                str(baseURL + pagination + endURL)
            ]
        
        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        page = response.url.split("&")[3].split("=")[1]
        filename = f'hdb-{page}.html'
        with open(filename, 'wb') as f:
            f.write(response.body)
        self.log(f'Saved file {filename}')

        next_page = response.css('li.next a').attrib['href']
        page_index = next_page.split("=")[1]
        if next_page is not None:
            nextURL = str(baseURL + page_index + endURL)
            next_page = response.urljoin(nextURL)
            yield scrapy.Request(next_page, callback=self.parse)