/*
  直接更新多个state方法的对象
*/

import {
  RECEIVE_PROBLEM_LIST,
  RECEIVE_PROBLEM_INFO
} from './mutation-types'

export default {
  [RECEIVE_PROBLEM_LIST] (state, {problemList}) {
    state.problemList = problemList
  },
  [RECEIVE_PROBLEM_INFO] (state, {problemInfo}) {
    state.problemInfo = problemInfo
  }
}
