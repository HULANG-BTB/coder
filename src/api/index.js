/*
包含结构请求函数的模块
*/

import ajax from './ajax'

const BASE_URL = '/api'

// 获取题目列表
export const reqProblemList = (query) => ajax(BASE_URL + `/api/Problem/getProblemList`, 'POST', query)
// 获取题目信息
export const reqProblemInfo = (query) => ajax(BASE_URL + `/api/Problem/getProblemInfo`, 'POST', query)
// 获取分类列表
export const reqCategoryList = () => ajax(BASE_URL + `/api/Category/getCategoryList`)
// 获取状态列表
export const reqStatusList = (query) => ajax(BASE_URL + `/api/Status/getStatusList`, 'POST', query)
// 提交登录表单
export const reqLoginSubmit = (query) => ajax(BASE_URL + `/api/User/login`, 'POST', query)
// 获取用户信息
export const reqUserInfo = () => ajax(BASE_URL + `/api/User/getUserInfo`)
// 请求注销登录
export const reqLogoutSubmit = () => ajax(BASE_URL + `/api/User/logout`)
