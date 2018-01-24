import { NgModule } from '@angular/core';

import { ThemeModule } from '../../../@theme/theme.module';
import { DomainComponent } from './domain.component';

const components = [
  DomainComponent,
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
export class DomainModule { }
