import { Component } from '@angular/core';

@Component({
  selector: 'ngx-footer',
  styleUrls: ['./footer.component.scss'],
  template: `
    <span class="created-by">Created with ♥ by <b><a color="white">Coquilletes Jambon</a></b> 2k17</span>
    <div class="socials">
      <a href="https://github.com/akveo" target="_blank" class="ion ion-social-github"></a>
      <a href="https://www.facebook.com/ethan.kerdelhue" target="_blank" class="ion ion-social-facebook"></a>
      <a href="https://twitter.com/damsweb" target="_blank" class="ion ion-social-twitter"></a>
    </div>
  `,
})
export class FooterComponent {
}
