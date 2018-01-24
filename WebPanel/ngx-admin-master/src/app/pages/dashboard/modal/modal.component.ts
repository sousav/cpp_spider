import { Component, ViewChild, ElementRef } from '@angular/core';
import { NgbActiveModal } from '@ng-bootstrap/ng-bootstrap';
import { AfterViewInit } from '@angular/core';
import { HttpClient } from '@angular/common/http'
import { Request, RequestMethod} from '@angular/http';
import { NgbModal } from '@ng-bootstrap/ng-bootstrap';
import { Headers, RequestOptions } from '@angular/http';
import { HttpHeaders } from '@angular/common/http';
import { ChangeDetectorRef } from '@angular/core';

@Component({
  selector: 'ngx-modal',
  template: `
    <div class="modal-header">
      <span>{{ modalHeader }}</span>
      <button class="close" aria-label="Close" (click)="closeModal()">
        <span aria-hidden="true">&times;</span>
      </button>

    </div>
    <div *ngIf="isConsoleMode == true">
        <div class="alert alert-hint" style="width:90%;margin-left: auto;margin-right: auto;margin-top:3%;">
            <table style="width:100%;">
                <tr>
                    <div  *ngFor="let item of modalCommandExec;">
                        <td> {{ item.str }} </td>
                    </div>
                </tr>
            </table>
        </div>
    </div>
    <div class="modal-body" #modalHtmlBody>
        <div *ngIf="isInfoMode == true">
            <table class="table-compact" style="width:90%; margin-top: 2%;">
                <thead>
                        <tr>
                                <th>Key</th>
                                <th>Value</th>
                        </tr>
                </thead>
                <tbody>
                    <tr *ngFor="let item of tableInfo;">
                        <td> {{ item.key }} </td>
                        <td> {{ item.value }} </td>
                    </tr>
                </tbody>
            </table>
        </div>
        <div *ngIf="isMouseMode == true">
            <table class="table-compact" style="width:90%; margin-top: 2%;">
                <thead>
                        <tr>
                                <th>X | Y</th>
                                <th>Right / Left</th>
                        </tr>
                </thead>
                <tbody>
                    <tr *ngFor="let item of tableInfo;">
                        <td> {{ item.key }} </td>
                        <td> {{ item.value }} </td>
                    </tr>
                </tbody>
            </table>
        </div>
        <div *ngIf="isLogMode == true">
            <nb-tabset fullWidth>

            <nb-tab tabTitle="All">
                <table class="table-compact" style="width:90%; margin-top: 2%;">
                    <thead>
                            <tr>
                                    <th> Time</th>
                                    <th>Application</th>
                                    <th>Text</th>
                            </tr>
                    </thead>
                    <tbody>
                        <tr *ngFor="let item of tableAll;">
                            <td> {{ item.time }} </td>
                            <td> {{ item.app }} </td>
                            <td> {{ item.text }} </td>
                        </tr>
                    </tbody>
                </table>
            </nb-tab>
            <nb-tab tabTitle="Search">
            <div _ngcontent-c45="" class="input-group" style="margin-top:2%;">
              <input _ngcontent-c45="" class="form-control" placeholder="Search for..." type="text" #searchField>
              <span _ngcontent-c45="" class="input-group-btn">
                <button _ngcontent-c45="" class="btn btn-success" (click)="makeSearch()">
                  Search
                </button>
              </span>
            </div>

            <table class="table-compact" style="width:90%; margin-top: 2%;">
                <thead>
                        <tr>
                                <th>Time</th>
                                <th>Application</th>
                                <th>Text</th>
                        </tr>
                </thead>
                <tbody>
                    <tr *ngFor="let item of searchResult;">
                        <td> {{ item.time }} </td>
                        <td> {{ item.app }} </td>
                        <td> {{ item.text }} </td>
                    </tr>
                </tbody>
            </table>

            </nb-tab>
            <nb-tab tabTittle="QSMDLKQMLSDKMQLSKD">

            </nb-tab>
            </nb-tabset>
        </div>
        <div *ngIf="isConsoleMode == true">
            <div _ngcontent-c23="" class="input-group">
                <input _ngcontent-c23="" class="form-control" placeholder="Command" type="text" #sendCmd>
                    <span _ngcontent-c23="" class="input-group-btn">
                        <button _ngcontent-c23="" (click)="sendingCmd()" class="btn btn-danger">Send</button>
                    </span>
            </div>
        </div>
        {{ modalBody }}
    </div>
    <div class="modal-footer">
      <button class="btn btn-md btn-primary" (click)="closeModal()">{{ modalFooter }}</button>
    </div>

  `,
})
export class ModalComponent {

  modalBody: any;
  modalFooter: string;
  client_id: string;
  tableAll: any;
  tableAccount: any;
  tableInfo: any;
  searchResult: any;
  applicationChoices: Array<string>;
  isConsoleMode: boolean;
  isInfoMode: boolean;
  isLogMode: boolean;
  isMouseMode: boolean;
  name: string;
  ip: string;
  modalCommandExec: any;
  modalHeader: string;
  modalContent: string = `Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy
    nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis
    nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat.`;

    @ViewChild('modalHtmlBody')modalHtmlBody: ElementRef;
    @ViewChild('searchField')searchField: ElementRef;
    @ViewChild('sendCmd')sendCmd: ElementRef;
    @ViewChild('logModApp')logModApp: ElementRef;
    @ViewChild('logModAll')logModAll: ElementRef;

  constructor(private activeModal: NgbActiveModal, private http: HttpClient) {
      this.modalCommandExec = [];
      this.applicationChoices = [];
      this.tableAll = [];
      this.tableInfo = [];
      this.tableAccount = [];
      this.setApplicationChoices();
  }

  setApplicationChoices() {

      for (var i = 0; i < this.tableAll.length; i++) {
          if (this.applicationChoices.indexOf(this.tableAll[i].app) == -1) {
              this.applicationChoices.push(this.tableAll[i].app);
          }
      }
      console.log(this.applicationChoices.length);
  }

  setupConsoleModal(name: string, ip: string) {
      this.isConsoleMode = true;
      this.ip = ip;
      this.client_id = name;
      this.name = name + "@" + ip;
  }

  setupInfoModal() {
      this.isInfoMode = true;
  }

  setupLogModal() {
      this.isLogMode = true;
      this.getAccount();
  }

  setupMouseModal() {
      this.isMouseMode = true;
  }

  closeModal() {
    this.activeModal.close();
  }

  addLineLog(time: string, app: string, text: string) {
      this.tableAll.push({
          time: time,
          app: app,
          text: text,
      });
  }

  addCommandExec(str: string) {
      this.modalCommandExec.push({str: this.name + "> " + str});

          var url = "http://93.9.51.53:3000/api/wp_exec";
          var headers = new HttpHeaders();
          var body =  JSON.stringify({client_id: this.client_id, command: str});
          console.log(body);
          headers.append('Content-Type', 'raw');
          this.http
            .post(url,
            body, {
              headers: headers
            })
            .subscribe(data => {
                this.getCommandResult();
          });
  }

  addResultExec(str: string) {
      this.modalCommandExec.push({str: this.name + "> " + str});
  }

  addLineInfo(key: string, value: string) {
      this.tableInfo.push({
          key: key,
          value: value,
      })
  }

  sendingCmd() {
    this.addCommandExec(this.sendCmd.nativeElement.value);
    this.sendCmd.nativeElement.value = "";
  }

  logModAppClick() {

  }

  logModAllClick() {

  }

  makeSearch() {
      var searchKey = this.searchField.nativeElement.value;

      this.searchResult = [];
      for(let item of this.tableAll) {
          if (item.app.indexOf(searchKey) !== -1) {
              this.searchResult.push(item);
          } else if (item.text.indexOf(searchKey) !== -1) {
              this.searchResult.push(item);
          }
      }
  }

  getAccount() {
      for (let item of this.tableAll) {
          console.log(item.text + " :")
          console.log(this.validateEmail(item.text));
      }
  }

  updateAccount () {
      console.log("on update l'account");
  }

  validateEmail(email: string) {
    var re = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    return re.test(email);
  }

  getCommandResult() {
      var url = "http://93.9.51.53:3000/api/wp_clients";
      if (this.modalCommandExec.length != 1) {
        this.modalCommandExec = [];
      }
      this.http
        .get(url)
        .subscribe((res:any) => {
            for (let item of res.Clients) {
                console.log(item);
                if (item.client_id == this.client_id) {
                    console.log("BBONJOUR JEXISTE")
                    for (let elem of item.ExecInfo) {
                        this.modalCommandExec.push({str: this.name + "> " + elem.result});
                        this.modalCommandExec.push({str: this.name + "> " + elem.command});
                    }
                    this.modalCommandExec.reverse();
                }
            }
      });
  }
}
