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
      component: Category => require(['@/views/Category/Category'], Category),
      children: [
        {
          path: '/Category/Index',
          name: 'CategoryIndex',
          component: CategoryIndex => require(['@/views/Category/Index'], CategoryIndex),
          query: {
            page: 1,
            limit: 15
          }
        },
        {
          path: '/Category/List',
          name: 'CategoryList',
          component: CategoryList => require(['@/views/Category/List'], CategoryList),
          query: {
            page: 1,
            limit: 15
          }
        },
        {
          path: '',
          redirect: '/Category/Index',
          query: {
            page: 1,
            limit: 15
          }
        }
      ]
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
      component: Problem => require(['@/views/Problem/Problem'], Problem),
      children: [
        {
          path: '/Problem/List',
          name: 'ProblemList',
          component: ProblemList => require(['@/views/Problem/List'], ProblemList),
          query: {
            page: 1,
            limit: 15
          }
        },
        {
          path: '/Problem/Detail',
          name: 'ProblemDetail',
          component: ProblemDetail => require(['@/views/Problem/Detail'], ProblemDetail),
          query: {
            id: 1
          }
        },
        {
          path: '/Problem/Submit',
          name: 'ProblemSubmit',
          component: ProblemSubmit => require(['@/views/Problem/Submit'], ProblemSubmit),
          query: {
            id: 1
          }
        },
        {
          path: '',
          redirect: '/Problem/List',
          query: {
            page: 1,
            limit: 15
          }
        }
      ]
    },
    {
      path: '/Status',
      component: Status => require(['@/views/Status/Status'], Status),
      children: [
        {
          path: '/Status/List',
          name: 'StatusList',
          component: StatusList => require(['@/views/Status/List'], StatusList),
          query: {
            page: 1,
            limit: 15,
            id: '',
            user: '',
            language: '',
            result: ''
          }
        },
        {
          path: '',
          redirect: '/Status/List',
          query: {
            page: 1,
            limit: 15,
            id: '',
            user: '',
            language: '',
            result: ''
          }
        }
      ]
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
