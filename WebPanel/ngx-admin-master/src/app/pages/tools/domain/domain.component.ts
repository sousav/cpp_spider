import { Component } from '@angular/core';
import { ViewChild, ElementRef} from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'ngx-domain',
  styleUrls: ['./domain.component.scss'],
  templateUrl: './domain.component.html',
})
export class DomainComponent {

    @ViewChild('domainList')domainList: ElementRef;
    @ViewChild('domainListAlert')domainListAlert: ElementRef;
    @ViewChild('domainListAlertError')domainListAlertError: ElementRef;

    @ViewChild('domainWhois')domainWhois: ElementRef;
    @ViewChild('domainWhoisAlert')domainWhoisAlert: ElementRef;
    @ViewChild('domainWhoistAlertError')domainWhoistAlertError: ElementRef;

    DomainIPWhois: String;

    DomainIPList: any;
    DomainTableInfos: any;

    constructor(private http: HttpClient) {
        this.DomainTableInfos = [];
    }

    getDomainList() {
        let _domain = this.domainList.nativeElement.value;

        this.http.get('http://api.c99.nl/domainhistory.php?key=RBQD8-T5WEE-4KM7Q-WZ7I8&domain=' + _domain, {responseType: 'text'}).subscribe(data => {
            console.log(data);
            if (data != "Could not find any history for " + _domain) {
                this.factoData(data);
                this.domainListAlert.nativeElement.style = "display:block;"
                this.domainListAlertError.nativeElement.style = "display:none;"
            } else {
                this.DomainIPList = data
                this.domainListAlertError.nativeElement.style = "display:block;"
                this.domainListAlert.nativeElement.style = "display:none;"
            }
        });
    }

    getDomainWhois() {
        let _domain = this.domainWhois.nativeElement.value;
        console.log('http://api.c99.nl/whois.php?key=RBQD8-T5WEE-4KM7Q-WZ7I8&domain=' + _domain);
        this.http.get('http://api.c99.nl/whois.php?key=RBQD8-T5WEE-4KM7Q-WZ7I8&domain=' + _domain, {responseType: 'text'}).subscribe(data => {
            console.log(data);
            this.domainWhoistAlertError.nativeElement.style = "display:block;";
            this.DomainIPWhois = data;
        })
    }

    replaceAll(str, find, replace) {
        return str.replace(new RegExp(find, 'g'), replace);
    }

    factoData(data: String) {
        let lineString = data.split(',');
        this.DomainTableInfos = [];
        for (var i = 0; i < lineString.length; i++) {
            console.log(lineString[i]);
            let colomn = lineString[i].split(' ');
            let date = new Date(colomn[0].slice(1,-1));
            var monthNames = ["January", "February", "March", "April", "May", "June",
              "July", "August", "September", "October", "November", "December"
            ];
            if (colomn[0] != "") {
                this.DomainTableInfos.push({
                  date: date.getDate() + " " + monthNames[date.getMonth()] + " " + date.getFullYear(),
                  ip: colomn[1],
                });
            } else if (colomn[1] != "") {
                let date = new Date(colomn[1].slice(1,-1));
                this.DomainTableInfos.push({
                  date: date.getDate() + " " + monthNames[date.getMonth()] + " " + date.getFullYear(),
                  ip: colomn[2],
                });
            }

            console.log(colomn);
        }
    }

}
