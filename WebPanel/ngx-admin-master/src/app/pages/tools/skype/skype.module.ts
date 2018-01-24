import { NgModule } from '@angular/core';

import { ThemeModule } from '../../../@theme/theme.module';
import { SkypeComponent } from './skype.component';

const components = [
  SkypeComponent,
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
export class SkypeModule { }
