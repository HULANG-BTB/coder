import Vue from 'vue'
import Router from 'vue-router'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/Environment',
      component: Environment => require(['@/views/Environment/Environment'], Environment)
    },
    {
      path: '/Question',
      component: Question => require(['@/views/Question/Question'], Question)
    },
    {
      path: '/Category',
      component: Category => require(['@/views/Category/Category'], Category)
    },
    {
      path: '/Rank',
      component: Rank => require(['@/views/Rank/Rank'], Rank)
    },
    {
      path: '/Contest',
      component: Contest => require(['@/views/Contest/Contest'], Contest)
    },
    {
      path: '/Problem',
      component: Problem => require(['@/views/Problem/Problem'], Problem)
    },
    {
      path: '/Status',
      component: Status => require(['@/views/Status/Status'], Status)
    },
    {
      path: '/Profile',
      component: Profile => require(['@/views/Profile/Profile'], Profile)
    },
    {
      path: '/',
      redirect: '/Environment'
    }
  ]
})
