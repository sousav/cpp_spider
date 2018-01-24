import { NgModule } from '@angular/core';
import { AngularEchartsModule } from 'ngx-echarts';

import { ModalComponent } from './modal/modal.component';

import { DdosComponent } from './ddos.component';
import { ThemeModule } from '../../@theme/theme.module';

import { TemperatureDraggerComponent } from './temperature-dragger/temperature-dragger.component';

@NgModule({
  imports: [
    AngularEchartsModule,
    ThemeModule,
  ],
  declarations: [
    DdosComponent,
    ModalComponent,
    TemperatureDraggerComponent,
  ],
  entryComponents: [
    ModalComponent,
  ],
})
export class DdosModule { }
