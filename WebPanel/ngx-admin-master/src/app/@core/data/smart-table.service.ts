import { Injectable, Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable()
export class SmartTableService {

        data;

        constructor(public http: HttpClient) {}

}
