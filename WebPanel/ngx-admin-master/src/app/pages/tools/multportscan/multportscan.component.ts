import { Component } from '@angular/core';
import { ViewChild, ElementRef} from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'ngx-multportscan',
  styleUrls: ['./multportscan.component.scss'],
  templateUrl: './multportscan.component.html',
})
export class MultPortScanComponent {
    @ViewChild('ip')ip: ElementRef;
    @ViewChild('loading')loading: ElementRef;
    @ViewChild('portScannerAlert')portScannerAlert: ElementRef;
    @ViewChild('scanMultiplePortButton')scanMultiplePortButton: ElementRef;

    PortScannerResult: any;

    constructor(private http: HttpClient) {

    }

    scanMultiplePort() {
        let _ip = this.ip.nativeElement.value;
        let tmpStrBeacauseJSSmeltShit
        this.portScannerAlert.nativeElement.style = "display:none;";
        this.loading.nativeElement.style = "display:block;";
        this.http.get('http://api.c99.nl/portscanner.php?key=RBQD8-T5WEE-4KM7Q-WZ7I8&host=' + _ip, {responseType: 'text'}).subscribe(data => {
            this.portScannerAlert.nativeElement.style = "display:block;";
            // not possible : data = data.slice(0, -1);
            this.loading.nativeElement.style = "display:none;";
            tmpStrBeacauseJSSmeltShit = data;
            this.PortScannerResult = tmpStrBeacauseJSSmeltShit.slice(0, -2) + ".";
        })
    }



}


// port : 3001
