import Vue from 'vue'
import Router from 'vue-router'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/Home',
      component: Home => require(['@/views/Home/Home'], Home)
    },
    {
      path: '/Question',
      component: Question => require(['@/views/Question/Question'], Question)
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
      redirect: '/Home'
    }
  ]
})
