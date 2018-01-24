import { NgModule } from '@angular/core';

import { ThemeModule } from '../../../@theme/theme.module';
import { MultPortScanComponent } from './multportscan.component';

const components = [
  MultPortScanComponent,
];

@NgModule({
  imports: [
    ThemeModule,
  ],
  exports: [
    ...components,
  ],
  declarations: [
    ...components,
  ],
  providers: [],
})
export class MultPortScanModule { }
