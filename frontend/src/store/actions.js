/*
  间接更新state的多个对象方法
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
import {
  reqProblemList,
  reqProblemInfo,
  reqCategoryList,
  reqStatusList,
  reqUserInfo,
  reqRankList,
  reqContestList
} from '../api'

export default {
  // 异步获取问题列表
  async getProblemList ({commit, state}, params) {
    // 发送异步ajax请求
    const {page, limit, type, keyword} = params
    const result = await reqProblemList({page, limit, type, keyword})
    if (result.code === 1) {
      const problemList = result.data
      commit(RECEIVE_PROBLEM_LIST, {problemList})
      // 提交一个mutation
    }
  },
  // 异步获取问题信息
  async getProblemInfo ({commit, state}, id) {
    // 发送异步ajax请求
    const result = await reqProblemInfo(id)
    if (result.code === 1) {
      const problemInfo = result.data
      commit(RECEIVE_PROBLEM_INFO, {problemInfo})
      // 提交一个mutation
    }
  },
  setProblemInfo ({commit, state}, query) {
    const problemInfo = query
    commit(CLEAR_USER_INFO, {problemInfo})
    // 提交一个mutation
  },
  // 异步获取分类列表
  async getCategoryList ({commit}) {
    const result = await reqCategoryList()
    if (result.code === 1) {
      const categoryList = result.data
      commit(RECEIVE_CATEGORY_LIST, {categoryList})
      // 提交一个mutation
    }
  },
  // 异步获取状态列表
  async getStatusList ({commit}, query) {
    const result = await reqStatusList(query)
    if (result.code === 1) {
      const statusList = result.data
      commit(RECEIVE_STATUS_LIST, {statusList})
      // 提交一个mutation
    }
  },
  // 异步获取用户信息
  async getUserInfo ({commit}, query) {
    const result = await reqUserInfo(query)
    if (result.code === 1) {
      const userInfo = result.data
      commit(RECEIVE_USER_INFO, {userInfo})
      // 提交一个mutation
    } else if (result.code === 0) {
      const userInfo = {}
      commit(RECEIVE_USER_INFO, {userInfo})
    }
  },
  // 异步获取排行列表
  async getRankList ({commit}, query) {
    const result = await reqRankList(query)
    if (result.code === 1) {
      const rankList = result.data
      commit(RECEIVE_RANK_LIST, {rankList})
      // 提交一个mutation
    }
  },
  // 异步获取测试列表
  async getContestList ({commit}, query) {
    const result = await reqContestList(query)
    if (result.code === 1) {
      const contestList = result.data
      commit(RECEIVE_CONTEST_LIST, {contestList})
      // 提交一个mutation
    }
  }
}
