/*
  间接更新state的多个对象方法
*/

import {
  RECEIVE_PROBLEM_LIST,
  RECEIVE_PROBLEM_INFO
} from './mutation-types'
import {
  reqProblemList,
  reqProblemInfo
} from '../api'

export default {
  // 异步获取问题列表
  async getProblemList ({commit, state}, page) {
    // 发送异步ajax请求
    const result = await reqProblemList(page)
    if (result.code === 1) {
      const problemList = result.data
      commit(RECEIVE_PROBLEM_LIST, {problemList})
      // 提交一个mutation
    }
  },
  // 异步获取问题信息
  async getProblemInfo ({commit, state}, id) {
    // 发送异步ajax请求
    const problemInfo = await reqProblemInfo(id)
    commit(RECEIVE_PROBLEM_INFO, {problemInfo})
    // 提交一个mutation
  }
}
