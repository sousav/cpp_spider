import { Component } from '@angular/core';
import { ViewChild, ElementRef} from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'ngx-skype',
  styleUrls: ['./skype.component.scss'],
  templateUrl: './skype.component.html',
})
export class SkypeComponent {

    @ViewChild('username')username: ElementRef;
    @ViewChild('usernameAlert')usernameAlert: ElementRef;
    @ViewChild('usernameAlertError')usernameAlertError: ElementRef;


    SkypeResolved: String;

    constructor(private http: HttpClient) {

    }

    resolveSkype() {
        let _username = this.username.nativeElement.value;
        this.http.get('https://webresolver.nl/api.php?key=QIOE8-L0ZJS-BTGFZ-8QEA3&json&action=resolve&string=' + _username).subscribe((res: any) => {
            console.log(res);
            if (res.success == true) {
                this.SkypeResolved = res.ip
                this.usernameAlert.nativeElement.style = "display:block;"
                this.usernameAlertError.nativeElement.style = "display:none;"
            } else {
                this.SkypeResolved = res.error
                this.usernameAlertError.nativeElement.style = "display:block;"
                this.usernameAlert.nativeElement.style = "display:none;"
            }
        });
    }

}
