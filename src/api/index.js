/*
包含结构请求函数的模块
*/

import ajax from './ajax'

const BASE_URL = '/api'

// 获取题目列表
export const reqProblemList = (page) => ajax(BASE_URL + `/api/Problem/getProblemList/page/${page}`)
// 获取题目信息
export const reqProblemInfo = (id) => ajax(BASE_URL + `/api/Problem/getProblemInfo/id/${id}`)
// 获取
