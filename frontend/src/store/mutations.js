/*
  直接更新多个state方法的对象
*/

import {
  RECEIVE_PROBLEM_LIST,
  RECEIVE_PROBLEM_INFO,
  CLEAR_USER_INFO,
  RECEIVE_CATEGORY_LIST,
  RECEIVE_STATUS_LIST,
  RECEIVE_USER_INFO,
  RECEIVE_RANK_LIST,
  RECEIVE_CONTEST_LIST
} from './mutation-types'

export default {
  [RECEIVE_PROBLEM_LIST] (state, {problemList}) {
    state.problemList = problemList
  },
  [RECEIVE_PROBLEM_INFO] (state, {problemInfo}) {
    state.problemInfo = problemInfo
  },
  [CLEAR_USER_INFO] (state, {problemInfo}) {
    state.problemInfo = problemInfo
  },
  [RECEIVE_CATEGORY_LIST] (state, {categoryList}) {
    state.categoryList = categoryList
  },
  [RECEIVE_STATUS_LIST] (state, {statusList}) {
    state.statusList = statusList
  },
  [RECEIVE_USER_INFO] (state, {userInfo}) {
    state.userInfo = userInfo
  },
  [RECEIVE_RANK_LIST] (state, {rankList}) {
    state.rankList = rankList
  },
  [RECEIVE_CONTEST_LIST] (state, {contestList}) {
    state.contestList = contestList
  }
}
