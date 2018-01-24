import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { ToolsComponent } from './tools.component';
import { DomainComponent } from './domain/domain.component';
import { SkypeComponent } from './skype/skype.component';
import { MultPortScanComponent } from './multportscan/multportscan.component';


const routes: Routes = [{
  path: '',
  component: ToolsComponent,
    children: [{
        path: 'skype',
        component: SkypeComponent,
    },
    {
        path: 'domain',
        component: DomainComponent,
    },
    {
        path: 'multportscan',
        component: MultPortScanComponent,
    }],
  }];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class ToolsRoutingModule { }
