import { NgModule } from '@angular/core';

import { PagesComponent } from './pages.component';
import { DashboardModule } from './dashboard/dashboard.module';
import { PagesRoutingModule } from './pages-routing.module';
import { ThemeModule } from '../@theme/theme.module';
import { DdosModule } from './ddos/ddos.module';
import { ToolsModule } from './tools/tools.module';

const PAGES_COMPONENTS = [
  PagesComponent,
];

@NgModule({
  imports: [
    PagesRoutingModule,
    ThemeModule,
    DashboardModule,
    DdosModule,
    ToolsModule,
  ],
  declarations: [
    ...PAGES_COMPONENTS,
  ],
})
export class PagesModule {
}
