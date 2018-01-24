import { NgModule } from '@angular/core';

import { ThemeModule } from '../../@theme/theme.module';
import { ToolsRoutingModule } from './tools-routing.module';
import { ToolsComponent } from './tools.component';
import { SkypeModule } from './skype/skype.module';
import { DomainModule } from './domain/domain.module';
import { MultPortScanModule } from './multportscan/multportscan.module';

const components = [
  ToolsComponent,
];

@NgModule({
  imports: [
    ThemeModule,
    ToolsRoutingModule,
    SkypeModule,
    DomainModule,
    MultPortScanModule,
  ],
  declarations: [
    ...components,
  ],
  entryComponents: [
  ],
})
export class ToolsModule { }
