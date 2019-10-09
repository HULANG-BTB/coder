<?php

namespace app\api\controller;

use app\common\controller\Base;
use app\api\model\Problem as ProblemModel;
use think\App;
use think\Controller;
use think\Request;

class Problem extends Base
{

    public function __construct(App $app = null)
    {
        parent::__construct($app);
        $this->Model = new ProblemModel();
    }

    /**
     * Notes: 获取题目列表
     * DateTime: 2019/9/27 13:29
     * Author: Hu Lang
     * Email: admin@oibit.cn
     * @return \think\response\Json
     * @throws \think\db\exception\DataNotFoundException
     * @throws \think\db\exception\ModelNotFoundException
     * @throws \think\exception\DbException
     */
    public function getProblemList()
    {
        /**
         * 获取post数据
         */
        $page = $this->request->post('page/d', 1);
        $limit = $this->request->post('limit/d', 15);
        $type = $this->request->post('type/s', '');
        $keyword = $this->request->post('keyword/s', '');

        /**
         * 查询数据
         */
        $result = $this->Model
            ->where(['status' => 1])
            ->where(isset($keyword) && isset($type) ? $type : 1, isset($keyword) && isset($type) ? 'like' : '=', '%'.$keyword.'%')
            ->page($page, $limit)
            ->field(['pid' => 'id', 'title', 'category', 'submit', 'solved'])
            ->order('id', 'asc')
            ->select();

        /**
         * 获取数据总条数
         */
        $count = $this->Model
            ->where(['status' => 1])
            ->where(isset($keyword) && isset($type) ? $type : 1, isset($keyword) && isset($type) ? 'like' : '=', '%'.$keyword.'%')
            ->count();

        /**
         * 构造返回结果
         */
        $ret = [
            'code' => 1,
            'data' => [
                'total' => $count,
                'page' => $page,
                'limit' => $limit,
                'data' => $result
            ]
        ];
        return json($ret);
    }

    /**
     * Notes: 查询题目信息
     * DateTime: 2019/9/27 13:31
     * Author: Hu Lang
     * Email: admin@oibit.cn
     * @return \think\response\Json
     * @throws \think\Exception\DbException
     */
    public function getProblemInfo()
    {
        $id = $this->request->post('id/d', 1000);
        $field = [
            'pid',
            'title',
            'description',
            'input',
            'output',
            'sample_input',
            'sample_output',
            'hint',
            'category',
            'time',
            'memory'
        ];
        $result = $this->Model
            ->field($field)
            ->get($id);
        $ret = [
            'code' => 1,
            'data' => $result
        ];
        return json($ret);
    }
}
