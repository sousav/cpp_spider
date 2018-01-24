import { NbMenuItem } from '@nebular/theme';

export const MENU_ITEMS: NbMenuItem[] = [
    {
        title: 'Dashboard',
        icon: 'nb-home',
        link: '/pages/dashboard',
        home: true,
    },
    {
        title: 'DDoS',
        icon: 'nb-flame-circled',
        link: '/pages/ddos',
    },
    {
        title: 'Tools',
        icon: 'nb-gear',
        link: '/pages/tools',
        children: [
            {
                title: 'Skype',
                link: '/pages/tools/skype',
            },
            {
                title: 'Domain',
                link: '/pages/tools/domain',
            },
            {
                title: 'Port Scanner',
                link: '/pages/tools/multportscan',
            }
        ],
    },
];
